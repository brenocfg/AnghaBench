#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct grub_obj_symbol {scalar_t__ segment; int name; int /*<<< orphan*/  offset; } ;
struct grub_obj_reloc_extern {scalar_t__ segment; int type; int addend; scalar_t__ symbol_segment; int symbol_name; int /*<<< orphan*/  offset; } ;
struct grub_obj_reloc {int dummy; } ;
struct grub_obj_header {int string_table; int symbol_table; int reloc_table; } ;
typedef  int grub_uint64_t ;
typedef  int grub_uint32_t ;
typedef  int grub_uint16_t ;
typedef  int grub_int32_t ;
typedef  int /*<<< orphan*/  grub_err_t ;
typedef  int /*<<< orphan*/  grub_dl_t ;
typedef  int grub_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  GRUB_ERR_BAD_MODULE ; 
 int /*<<< orphan*/  GRUB_ERR_NONE ; 
 int GRUB_OBJ_REL_FLAG_REL ; 
#define  GRUB_OBJ_REL_TYPE_16 138 
#define  GRUB_OBJ_REL_TYPE_16HA 137 
#define  GRUB_OBJ_REL_TYPE_16HI 136 
#define  GRUB_OBJ_REL_TYPE_24 135 
#define  GRUB_OBJ_REL_TYPE_30 134 
#define  GRUB_OBJ_REL_TYPE_32 133 
#define  GRUB_OBJ_REL_TYPE_64 132 
#define  GRUB_OBJ_REL_TYPE_HH22 131 
#define  GRUB_OBJ_REL_TYPE_HI22 130 
#define  GRUB_OBJ_REL_TYPE_HM10 129 
#define  GRUB_OBJ_REL_TYPE_LO10 128 
 int GRUB_OBJ_REL_TYPE_MASK ; 
 scalar_t__ GRUB_OBJ_SEGMENT_END ; 
 char* grub_dl_get_section_addr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ grub_dl_register_symbol (char*,char*,int /*<<< orphan*/ ) ; 
 char* grub_dl_resolve_symbol (char*) ; 
 int /*<<< orphan*/  grub_errno ; 
 int /*<<< orphan*/  grub_error (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static grub_err_t
grub_dl_resolve_symbols (grub_dl_t mod, struct grub_obj_header *e)
{
  char *strtab;
  struct grub_obj_symbol *sym;
  struct grub_obj_reloc_extern *rel;

  strtab = (char *) e + e->string_table;

  for (sym = (struct grub_obj_symbol *) ((char *) e + e->symbol_table);
       sym->segment != GRUB_OBJ_SEGMENT_END; sym++)
    {
      char *addr;

      addr = grub_dl_get_section_addr (mod, sym->segment);
      addr += sym->offset;

      if (grub_dl_register_symbol (strtab + sym->name, addr, mod))
	return grub_errno;
    }

  for (rel = (struct grub_obj_reloc_extern *) ((char *) e + e->reloc_table);
       rel->segment != GRUB_OBJ_SEGMENT_END;)
    {
      char *addr, *symbol_addr;
      grub_addr_t addend;
      int type;

      addr = grub_dl_get_section_addr (mod, rel->segment);
      addr += rel->offset;
      type = rel->type;

#if defined(GRUB_TARGET_USE_ADDEND)
      addend = rel->addend;
#else
      addend = *((grub_addr_t *) addr);
#endif

      if (rel->symbol_segment == GRUB_OBJ_SEGMENT_END)
	{
	  char *name;

	  name = strtab + rel->symbol_name;
	  symbol_addr = grub_dl_resolve_symbol (name);
	  if (! symbol_addr)
	    return grub_error (GRUB_ERR_BAD_MODULE,
			       "symbol not found: `%s'", name);
	  rel++;
	}
      else
	{
	  symbol_addr = grub_dl_get_section_addr (mod, rel->symbol_segment);
	  rel = (struct grub_obj_reloc_extern *)
	    ((char *) rel + sizeof (struct grub_obj_reloc));
	}

      addend += (grub_addr_t) symbol_addr;
      if (type & GRUB_OBJ_REL_FLAG_REL)
	addend -= (grub_addr_t) addr;

      type &= GRUB_OBJ_REL_TYPE_MASK;
      switch (type)
	{
	case GRUB_OBJ_REL_TYPE_32:
	  *((grub_uint32_t *) addr) = addend;
	  break;

#if GRUB_TARGET_SIZEOF_VOID_P == 8
	case GRUB_OBJ_REL_TYPE_64:
	  *((grub_uint64_t *) addr) = addend;
	  break;
#endif

#if defined(GRUB_TARGET_POWERPC)
	case GRUB_OBJ_REL_TYPE_16:
	  *((grub_uint16_t *) addr) = addend;
	  break;

	case GRUB_OBJ_REL_TYPE_16HI:
	  *((grub_uint16_t *) addr) = addend >> 16;
	  break;

	case GRUB_OBJ_REL_TYPE_16HA:
	  *((grub_uint16_t *) addr) = (addend + 0x8000) >> 16;
	  break;

	case GRUB_OBJ_REL_TYPE_24:
	  {
	    grub_uint32_t v;
	    grub_int32_t a;

	    v = *((grub_uint32_t *) addr);
	    a = addend;

	    if (a << 6 >> 6 != a)
	      return grub_error (GRUB_ERR_BAD_MODULE, "relocation overflow");

	    v = (v & 0xfc000003) | (addend & 0x3fffffc);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }
#endif

#if defined(GRUB_TARGET_SPARC64)
	case GRUB_OBJ_REL_TYPE_LO10:
	  {
	    grub_uint32_t v;

	    v = *((grub_uint32_t *) addr);
	    v = (v & ~0x3ff) | (addend & 0x3ff);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }

	case GRUB_OBJ_REL_TYPE_HI22:
	  {
	    grub_uint32_t v;

	    v = *((grub_uint32_t *) addr);
	    v = (v & ~0x3fffff) | ((addend >> 10) & 0x3fffff);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }

#if GRUB_TARGET_SIZEOF_VOID_P == 8
	case GRUB_OBJ_REL_TYPE_HM10:
	  {
	    grub_uint32_t v;

	    v = *((grub_uint32_t *) addr);
	    v = (v & ~0x3ff) | ((addend >> 32) & 0x3ff);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }

	case GRUB_OBJ_REL_TYPE_HH22:
	  {
	    grub_uint32_t v;

	    v = *((grub_uint32_t *) addr);
	    v = (v & ~0x3fffff) | ((addend >> 42) & 0x3fffff);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }
#endif

	case GRUB_OBJ_REL_TYPE_30:
	  {
	    grub_uint32_t v;
	    grub_int32_t a;

	    v = *((grub_uint32_t *) addr);
	    a = addend;

	    if (a << 2 >> 2 != a)
	      return grub_error (GRUB_ERR_BAD_MODULE, "relocation overflow");

	    v = (v & 0xc0000000) | ((addend >> 2) & 0x3fffffff);
	    *((grub_uint32_t *) addr) = v;
	    break;
	  }
#endif

	default:
	  return grub_error (GRUB_ERR_BAD_MODULE,
			     "unknown reloc type %d", type);
	}
    }

  return GRUB_ERR_NONE;
}
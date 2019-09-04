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
struct disassemble_info {int dummy; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static int
get_sym_code_type (struct disassemble_info *info,
		   int n,
		   enum map_type *map_type)
{
return FALSE;
#if 0
  elf_symbol_type *es;
  unsigned int type;

  /* If the symbol is in a different section, ignore it.  */
  if (info->section != NULL && info->section != info->symtab[n]->section)
    return FALSE;

  es = *(elf_symbol_type **)(info->symtab + n);
  type = ELF_ST_TYPE (es->internal_elf_sym.st_info);

  /* If the symbol has function type then use that.  */
  if (type == STT_FUNC || type == STT_GNU_IFUNC)
    {
      if (ARM_GET_SYM_BRANCH_TYPE (es->internal_elf_sym.st_target_internal)
	  == ST_BRANCH_TO_THUMB)
	*map_type = MAP_THUMB;
      else
	*map_type = MAP_ARM;
      return TRUE;
    }

  return FALSE;
#endif
}
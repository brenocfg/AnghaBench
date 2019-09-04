#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {TYPE_3__** symtab; int /*<<< orphan*/ * section; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_4__ {int /*<<< orphan*/  st_info; } ;
struct TYPE_5__ {TYPE_1__ internal_elf_sym; } ;
typedef  TYPE_2__ elf_symbol_type ;
struct TYPE_6__ {int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 unsigned int ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int MAP_DATA ; 
 int MAP_INSN ; 
 unsigned int STT_FUNC ; 
 int TRUE ; 
 char* bfd_asymbol_name (TYPE_3__*) ; 

__attribute__((used)) static int
get_sym_code_type (struct disassemble_info *info, int n,
		   enum map_type *map_type)
{
  elf_symbol_type *es;
  unsigned int type;
  const char *name;

  /* If the symbol is in a different section, ignore it.  */
  if (info->section != NULL && info->section != info->symtab[n]->section)
    return FALSE;

  es = *(elf_symbol_type **)(info->symtab + n);
  type = ELF_ST_TYPE (es->internal_elf_sym.st_info);

  /* If the symbol has function type then use that.  */
  if (type == STT_FUNC)
    {
      *map_type = MAP_INSN;
      return TRUE;
    }

  /* Check for mapping symbols.  */
  name = bfd_asymbol_name(info->symtab[n]);
  if (name[0] == '$'
      && (name[1] == 'x' || name[1] == 'd')
      && (name[2] == '\0' || name[2] == '.'))
    {
      *map_type = (name[1] == 'x' ? MAP_INSN : MAP_DATA);
      return TRUE;
    }

  return FALSE;
}
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
struct disassemble_info {scalar_t__ symtab_size; int /*<<< orphan*/ * symtab; struct arm_private_data* private_data; } ;
struct arm_private_data {int last_mapping_sym; int has_mapping_symbols; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAP_ARM ; 
 int MAP_DATA ; 
 scalar_t__ TRUE ; 
 scalar_t__ bfd_asymbol_flavour (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_asymbol_value (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_elf_flavour ; 
 scalar_t__ get_map_sym_type (struct disassemble_info*,int,int*) ; 

__attribute__((used)) static bfd_boolean
mapping_symbol_for_insn (bfd_vma pc, struct disassemble_info *info,
			 enum map_type *map_symbol)
{
  bfd_vma addr;
  int n, start = 0;
  bfd_boolean found = FALSE;
  enum map_type type = MAP_ARM;
  struct arm_private_data *private_data;

  if (info->private_data == NULL || info->symtab_size == 0 || bfd_asymbol_flavour (*info->symtab) != bfd_target_elf_flavour) {
	  return FALSE;
  }

  private_data = info->private_data;
  if (pc == 0) {
	  start = 0;
  } else {
	  start = private_data->last_mapping_sym;
  }

  start = (start == -1)? 0 : start;
  addr = bfd_asymbol_value (info->symtab[start]);

  if (pc >= addr)
    {
	  if (get_map_sym_type (info, start, &type)) {
		  found = TRUE;
	  }
    }
  else
    {
      for (n = start - 1; n >= 0; n--)
	{
	  if (get_map_sym_type (info, n, &type))
	    {
	      found = TRUE;
	      break;
	    }
	}
    }

  /* No mapping symbols were found.  A leading $d may be
     omitted for sections which start with data; but for
     compatibility with legacy and stripped binaries, only
     assume the leading $d if there is at least one mapping
     symbol in the file.  */
  if (!found && private_data->has_mapping_symbols == 1)
    {
      type = MAP_DATA;
      found = TRUE;
    }

  *map_symbol = type;
  return found;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {TYPE_1__** symtab; int /*<<< orphan*/ * section; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;
struct TYPE_2__ {int /*<<< orphan*/ * section; } ;

/* Variables and functions */
 int FALSE ; 
 int is_mapping_symbol (struct disassemble_info*,int,int*) ; 

__attribute__((used)) static int
get_map_sym_type (struct disassemble_info *info,
		  int n,
		  enum map_type *map_type)
{
  /* If the symbol is in a different section, ignore it.  */
  if (info->section != NULL && info->section != info->symtab[n]->section) {
	  return FALSE;
  }

  return is_mapping_symbol (info, n, map_type);
}
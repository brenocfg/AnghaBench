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
struct disassemble_info {int /*<<< orphan*/ * symtab; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 int FALSE ; 
 int MAP_ARM ; 
 int MAP_DATA ; 
 int MAP_THUMB ; 
 int TRUE ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
is_mapping_symbol (struct disassemble_info *info, int n,
		   enum map_type *map_type)
{
  const char *name;

  name = bfd_asymbol_name (info->symtab[n]);
  if (name[0] == '$' && (name[1] == 'a' || name[1] == 't' || name[1] == 'd')
      && (name[2] == 0 || name[2] == '.'))
    {
      *map_type = ((name[1] == 'a') ? MAP_ARM
		   : (name[1] == 't') ? MAP_THUMB
		   : MAP_DATA);
      return TRUE;
    }

  return FALSE;
}
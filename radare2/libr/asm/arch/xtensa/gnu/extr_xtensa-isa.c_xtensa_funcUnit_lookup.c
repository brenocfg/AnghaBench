#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fun; } ;
struct TYPE_7__ {char const* key; TYPE_1__ u; } ;
typedef  TYPE_2__ xtensa_lookup_entry ;
struct TYPE_8__ {scalar_t__ num_funcUnits; int /*<<< orphan*/  funcUnit_lookup_table; } ;
typedef  TYPE_3__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
typedef  int /*<<< orphan*/  xtensa_funcUnit ;

/* Variables and functions */
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 
 TYPE_2__* bsearch (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xtensa_isa_bad_funcUnit ; 
 int /*<<< orphan*/  xtensa_isa_name_compare ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_funcUnit
xtensa_funcUnit_lookup (xtensa_isa isa, const char *fname)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  xtensa_lookup_entry entry, *result = 0;

  if (!fname || !*fname)
    {
      xtisa_errno = xtensa_isa_bad_funcUnit;
      strcpy (xtisa_error_msg, "invalid functional unit name");
      return XTENSA_UNDEFINED;
    }

  if (intisa->num_funcUnits != 0)
    {
      entry.key = fname;
      result = bsearch (&entry, intisa->funcUnit_lookup_table,
			intisa->num_funcUnits, sizeof (xtensa_lookup_entry),
			xtensa_isa_name_compare);
    }

  if (!result)
    {
      xtisa_errno = xtensa_isa_bad_funcUnit;
      sprintf (xtisa_error_msg,
	       "functional unit \"%s\" not recognized", fname);
      return XTENSA_UNDEFINED;
    }

  return result->u.fun;
}
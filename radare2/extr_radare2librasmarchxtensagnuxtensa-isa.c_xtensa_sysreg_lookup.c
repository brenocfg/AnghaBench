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
typedef  scalar_t__ xtensa_sysreg ;
struct TYPE_2__ {int* max_sysreg_num; scalar_t__** sysreg_table; } ;
typedef  TYPE_1__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;

/* Variables and functions */
 scalar_t__ XTENSA_UNDEFINED ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xtensa_isa_bad_sysreg ; 
 int /*<<< orphan*/  xtisa_errno ; 
 int /*<<< orphan*/  xtisa_error_msg ; 

xtensa_sysreg
xtensa_sysreg_lookup (xtensa_isa isa, int num, int is_user)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;

  if (is_user != 0) {
	  is_user = 1;
  }

  if (num < 0 || num > intisa->max_sysreg_num[is_user]
      || intisa->sysreg_table[is_user][num] == XTENSA_UNDEFINED)
    {
      xtisa_errno = xtensa_isa_bad_sysreg;
      strcpy (xtisa_error_msg, "sysreg not recognized");
      return XTENSA_UNDEFINED;
    }

  return intisa->sysreg_table[is_user][num];
}
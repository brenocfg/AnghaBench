#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xtensa_sysreg ;
struct TYPE_5__ {TYPE_1__* sysregs; } ;
typedef  TYPE_2__ xtensa_isa_internal ;
typedef  scalar_t__ xtensa_isa ;
struct TYPE_4__ {scalar_t__ is_user; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SYSREG (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XTENSA_UNDEFINED ; 

int
xtensa_sysreg_is_user (xtensa_isa isa, xtensa_sysreg sysreg)
{
  xtensa_isa_internal *intisa = (xtensa_isa_internal *) isa;
  CHECK_SYSREG (intisa, sysreg, XTENSA_UNDEFINED);
  if (intisa->sysregs[sysreg].is_user) {
	  return 1;
  }
  return 0;
}
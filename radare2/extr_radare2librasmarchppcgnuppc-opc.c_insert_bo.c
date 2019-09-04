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
typedef  int /*<<< orphan*/  ppc_cpu_t ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  valid_bo (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long
insert_bo (unsigned long insn,
	   long value,
	   ppc_cpu_t dialect,
	   const char **errmsg)
{
	if (!valid_bo (value, dialect, 0)) {
		*errmsg = _ ("invalid conditional option");
	}
	return insn | ((value & 0x1f) << 21);
}
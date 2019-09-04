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

/* Variables and functions */
 int KDB_BADREG ; 
 int /*<<< orphan*/  kdb_current_regs ; 
 int /*<<< orphan*/  kdb_printf (char*) ; 

__attribute__((used)) static int kdb_check_regs(void)
{
	if (!kdb_current_regs) {
		kdb_printf("No current kdb registers."
			   "  You may need to select another task\n");
		return KDB_BADREG;
	}
	return 0;
}
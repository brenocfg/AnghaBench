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
typedef  int /*<<< orphan*/  REgg ;

/* Variables and functions */
 int R_SZ ; 
 int /*<<< orphan*/  r_egg_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * regs ; 

__attribute__((used)) static void emit_syscall_args(REgg *egg, int nargs) {
	int j, k;
	for (j = 0; j < nargs; j++) {
		k = j * R_SZ;
		r_egg_printf (egg, "  ldr %s, [sp, %d]\n",
			regs[j + 1], k? k + 4: k + 8);
	}
}
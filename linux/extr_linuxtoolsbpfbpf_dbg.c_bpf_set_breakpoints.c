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
 int array_size (int*) ; 
 int* bpf_breakpoints ; 
 int /*<<< orphan*/  rl_printf (char*) ; 

__attribute__((used)) static void bpf_set_breakpoints(unsigned int where)
{
	int i;
	bool set = false;

	for (i = 0; i < array_size(bpf_breakpoints); i++) {
		if (bpf_breakpoints[i] == (int) where) {
			rl_printf("breakpoint already set!\n");
			set = true;
			break;
		}

		if (bpf_breakpoints[i] == -1 && set == false) {
			bpf_breakpoints[i] = where;
			set = true;
		}
	}

	if (!set)
		rl_printf("too many breakpoints set, reset first!\n");
}
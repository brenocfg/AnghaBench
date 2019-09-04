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

__attribute__((used)) static void bpf_reset_breakpoints(void)
{
	int i;

	for (i = 0; i < array_size(bpf_breakpoints); i++)
		bpf_breakpoints[i] = -1;
}
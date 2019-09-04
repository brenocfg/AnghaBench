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
 int /*<<< orphan*/  XSTATE_CPUID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpuid_count (int /*<<< orphan*/ ,int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 unsigned int one_bit (unsigned int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

void print_state_component(int state_bit_nr, char *name)
{
	unsigned int eax, ebx, ecx, edx;
	unsigned int state_component_size;
	unsigned int state_component_supervisor;
	unsigned int state_component_user;
	unsigned int state_component_aligned;

	/* See SDM Section 13.2 */
	cpuid_count(XSTATE_CPUID, state_bit_nr, &eax, &ebx, &ecx, &edx);
	assert(eax || ebx || ecx);
	state_component_size = eax;
	state_component_supervisor = ((!ebx) && one_bit(ecx, 0));
	state_component_user = !one_bit(ecx, 0);
	state_component_aligned = one_bit(ecx, 1);
	printf("%8s: size: %d user: %d supervisor: %d aligned: %d\n",
		name,
		state_component_size,	    state_component_user,
		state_component_supervisor, state_component_aligned);

}
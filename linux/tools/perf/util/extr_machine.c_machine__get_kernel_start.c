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
struct map {unsigned long long start; } ;
struct machine {unsigned long long kernel_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  machine__is (struct machine*,char*) ; 
 struct map* machine__kernel_map (struct machine*) ; 
 int map__load (struct map*) ; 

int machine__get_kernel_start(struct machine *machine)
{
	struct map *map = machine__kernel_map(machine);
	int err = 0;

	/*
	 * The only addresses above 2^63 are kernel addresses of a 64-bit
	 * kernel.  Note that addresses are unsigned so that on a 32-bit system
	 * all addresses including kernel addresses are less than 2^32.  In
	 * that case (32-bit system), if the kernel mapping is unknown, all
	 * addresses will be assumed to be in user space - see
	 * machine__kernel_ip().
	 */
	machine->kernel_start = 1ULL << 63;
	if (map) {
		err = map__load(map);
		/*
		 * On x86_64, PTI entry trampolines are less than the
		 * start of kernel text, but still above 2^63. So leave
		 * kernel_start = 1ULL << 63 for x86_64.
		 */
		if (!err && !machine__is(machine, "x86_64"))
			machine->kernel_start = map->start;
	}
	return err;
}
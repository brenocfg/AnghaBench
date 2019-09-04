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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct thread {int dummy; } ;
struct addr_location {scalar_t__ map; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  const PERF_RECORD_MISC_GUEST_USER ; 
 int /*<<< orphan*/  const PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  const PERF_RECORD_MISC_USER ; 
 int /*<<< orphan*/  thread__find_symbol (struct thread*,int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct addr_location*) ; 

void thread__find_cpumode_addr_location(struct thread *thread, u64 addr,
					struct addr_location *al)
{
	size_t i;
	const u8 cpumodes[] = {
		PERF_RECORD_MISC_USER,
		PERF_RECORD_MISC_KERNEL,
		PERF_RECORD_MISC_GUEST_USER,
		PERF_RECORD_MISC_GUEST_KERNEL
	};

	for (i = 0; i < ARRAY_SIZE(cpumodes); i++) {
		thread__find_symbol(thread, cpumodes[i], addr, al);
		if (al->map)
			break;
	}
}
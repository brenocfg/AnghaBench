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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct thread {TYPE_1__* mg; } ;
struct map {int dummy; } ;
struct machine {int dummy; } ;
struct addr_location {int dummy; } ;
struct TYPE_2__ {struct machine* machine; } ;

/* Variables and functions */
 scalar_t__ machine__addr_cpumode (struct machine*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct map* thread__find_map (struct thread*,scalar_t__,int /*<<< orphan*/ ,struct addr_location*) ; 

struct map *thread__find_map_fb(struct thread *thread, u8 cpumode, u64 addr,
				struct addr_location *al)
{
	struct map *map = thread__find_map(thread, cpumode, addr, al);
	struct machine *machine = thread->mg->machine;
	u8 addr_cpumode = machine__addr_cpumode(machine, cpumode, addr);

	if (map || addr_cpumode == cpumode)
		return map;

	return thread__find_map(thread, addr_cpumode, addr, al);
}
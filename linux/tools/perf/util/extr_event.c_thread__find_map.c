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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct thread {struct map_groups* mg; } ;
struct map_groups {struct machine* machine; } ;
struct map {int /*<<< orphan*/  (* map_ip ) (struct map*,int /*<<< orphan*/ ) ;} ;
struct machine {struct map_groups kmaps; } ;
struct addr_location {int filtered; char level; struct map* map; int /*<<< orphan*/  addr; scalar_t__ cpumode; struct thread* thread; struct machine* machine; } ;

/* Variables and functions */
 int HIST_FILTER__GUEST ; 
 int HIST_FILTER__HOST ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_GUEST_USER ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 scalar_t__ PERF_RECORD_MISC_USER ; 
 int /*<<< orphan*/  map__load (struct map*) ; 
 struct map* map_groups__find (struct map_groups*,int /*<<< orphan*/ ) ; 
 scalar_t__ perf_guest ; 
 scalar_t__ perf_host ; 
 int /*<<< orphan*/  stub1 (struct map*,int /*<<< orphan*/ ) ; 

struct map *thread__find_map(struct thread *thread, u8 cpumode, u64 addr,
			     struct addr_location *al)
{
	struct map_groups *mg = thread->mg;
	struct machine *machine = mg->machine;
	bool load_map = false;

	al->machine = machine;
	al->thread = thread;
	al->addr = addr;
	al->cpumode = cpumode;
	al->filtered = 0;

	if (machine == NULL) {
		al->map = NULL;
		return NULL;
	}

	if (cpumode == PERF_RECORD_MISC_KERNEL && perf_host) {
		al->level = 'k';
		mg = &machine->kmaps;
		load_map = true;
	} else if (cpumode == PERF_RECORD_MISC_USER && perf_host) {
		al->level = '.';
	} else if (cpumode == PERF_RECORD_MISC_GUEST_KERNEL && perf_guest) {
		al->level = 'g';
		mg = &machine->kmaps;
		load_map = true;
	} else if (cpumode == PERF_RECORD_MISC_GUEST_USER && perf_guest) {
		al->level = 'u';
	} else {
		al->level = 'H';
		al->map = NULL;

		if ((cpumode == PERF_RECORD_MISC_GUEST_USER ||
			cpumode == PERF_RECORD_MISC_GUEST_KERNEL) &&
			!perf_guest)
			al->filtered |= (1 << HIST_FILTER__GUEST);
		if ((cpumode == PERF_RECORD_MISC_USER ||
			cpumode == PERF_RECORD_MISC_KERNEL) &&
			!perf_host)
			al->filtered |= (1 << HIST_FILTER__HOST);

		return NULL;
	}

	al->map = map_groups__find(mg, al->addr);
	if (al->map != NULL) {
		/*
		 * Kernel maps might be changed when loading symbols so loading
		 * must be done prior to using kernel maps.
		 */
		if (load_map)
			map__load(al->map);
		al->addr = al->map->map_ip(al->map, al->addr);
	}

	return al->map;
}
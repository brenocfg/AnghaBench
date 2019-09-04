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
typedef  scalar_t__ u64 ;
struct symbol {scalar_t__ binding; int /*<<< orphan*/  start; int /*<<< orphan*/  name; } ;
struct map {scalar_t__ (* unmap_ip ) (struct map*,int /*<<< orphan*/ ) ;scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  dso; } ;
struct machine {int dummy; } ;
struct intel_pt {int have_sched_switch; struct machine* machine; } ;

/* Variables and functions */
 scalar_t__ STB_GLOBAL ; 
 struct symbol* dso__first_symbol (int /*<<< orphan*/ ) ; 
 struct symbol* dso__next_symbol (struct symbol*) ; 
 struct map* machine__kernel_map (struct machine*) ; 
 scalar_t__ map__load (struct map*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ stub1 (struct map*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct map*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 intel_pt_switch_ip(struct intel_pt *pt, u64 *ptss_ip)
{
	struct machine *machine = pt->machine;
	struct map *map;
	struct symbol *sym, *start;
	u64 ip, switch_ip = 0;
	const char *ptss;

	if (ptss_ip)
		*ptss_ip = 0;

	map = machine__kernel_map(machine);
	if (!map)
		return 0;

	if (map__load(map))
		return 0;

	start = dso__first_symbol(map->dso);

	for (sym = start; sym; sym = dso__next_symbol(sym)) {
		if (sym->binding == STB_GLOBAL &&
		    !strcmp(sym->name, "__switch_to")) {
			ip = map->unmap_ip(map, sym->start);
			if (ip >= map->start && ip < map->end) {
				switch_ip = ip;
				break;
			}
		}
	}

	if (!switch_ip || !ptss_ip)
		return 0;

	if (pt->have_sched_switch == 1)
		ptss = "perf_trace_sched_switch";
	else
		ptss = "__perf_event_task_sched_out";

	for (sym = start; sym; sym = dso__next_symbol(sym)) {
		if (!strcmp(sym->name, ptss)) {
			ip = map->unmap_ip(map, sym->start);
			if (ip >= map->start && ip < map->end) {
				*ptss_ip = ip;
				break;
			}
		}
	}

	return switch_ip;
}
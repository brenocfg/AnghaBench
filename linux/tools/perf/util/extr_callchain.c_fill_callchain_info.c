#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct callchain_cursor_node {int /*<<< orphan*/  ip; int /*<<< orphan*/  srcline; int /*<<< orphan*/ * sym; TYPE_1__* map; } ;
struct addr_location {char level; int /*<<< orphan*/  cpumode; TYPE_2__* machine; TYPE_1__* map; int /*<<< orphan*/ * sym; int /*<<< orphan*/  addr; int /*<<< orphan*/  srcline; } ;
struct TYPE_4__ {int /*<<< orphan*/  kmaps; } ;
struct TYPE_3__ {int /*<<< orphan*/ * groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_GUEST_USER ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_HYPERVISOR ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 scalar_t__ machine__is_host (TYPE_2__*) ; 
 scalar_t__ perf_guest ; 

int fill_callchain_info(struct addr_location *al, struct callchain_cursor_node *node,
			bool hide_unresolved)
{
	al->map = node->map;
	al->sym = node->sym;
	al->srcline = node->srcline;
	al->addr = node->ip;

	if (al->sym == NULL) {
		if (hide_unresolved)
			return 0;
		if (al->map == NULL)
			goto out;
	}

	if (al->map->groups == &al->machine->kmaps) {
		if (machine__is_host(al->machine)) {
			al->cpumode = PERF_RECORD_MISC_KERNEL;
			al->level = 'k';
		} else {
			al->cpumode = PERF_RECORD_MISC_GUEST_KERNEL;
			al->level = 'g';
		}
	} else {
		if (machine__is_host(al->machine)) {
			al->cpumode = PERF_RECORD_MISC_USER;
			al->level = '.';
		} else if (perf_guest) {
			al->cpumode = PERF_RECORD_MISC_GUEST_USER;
			al->level = 'u';
		} else {
			al->cpumode = PERF_RECORD_MISC_HYPERVISOR;
			al->level = 'H';
		}
	}

out:
	return 1;
}
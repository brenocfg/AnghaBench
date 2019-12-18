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
struct thread {int dummy; } ;
struct perf_sample {int /*<<< orphan*/  cpu; int /*<<< orphan*/  addr; int /*<<< orphan*/  cpumode; } ;
struct addr_location {int /*<<< orphan*/  addr; scalar_t__ map; int /*<<< orphan*/ * sym; int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/ * map__find_symbol (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__find_map_fb (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 

void thread__resolve(struct thread *thread, struct addr_location *al,
		     struct perf_sample *sample)
{
	thread__find_map_fb(thread, sample->cpumode, sample->addr, al);

	al->cpu = sample->cpu;
	al->sym = NULL;

	if (al->map)
		al->sym = map__find_symbol(al->map, al->addr);
}
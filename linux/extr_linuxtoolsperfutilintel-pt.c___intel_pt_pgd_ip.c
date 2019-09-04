#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
struct thread {int dummy; } ;
struct intel_pt_queue {TYPE_3__* pt; struct thread* thread; } ;
struct addr_location {TYPE_2__* map; } ;
struct TYPE_6__ {scalar_t__ kernel_start; } ;
struct TYPE_5__ {scalar_t__ (* map_ip ) (TYPE_2__*,scalar_t__) ;TYPE_1__* dso; } ;
struct TYPE_4__ {int /*<<< orphan*/ * long_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 int intel_pt_match_pgd_ip (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,int /*<<< orphan*/ ,scalar_t__,struct addr_location*) ; 

__attribute__((used)) static int __intel_pt_pgd_ip(uint64_t ip, void *data)
{
	struct intel_pt_queue *ptq = data;
	struct thread *thread;
	struct addr_location al;
	u8 cpumode;
	u64 offset;

	if (ip >= ptq->pt->kernel_start)
		return intel_pt_match_pgd_ip(ptq->pt, ip, ip, NULL);

	cpumode = PERF_RECORD_MISC_USER;

	thread = ptq->thread;
	if (!thread)
		return -EINVAL;

	if (!thread__find_map(thread, cpumode, ip, &al) || !al.map->dso)
		return -EINVAL;

	offset = al.map->map_ip(al.map, ip);

	return intel_pt_match_pgd_ip(ptq->pt, ip, offset,
				     al.map->dso->long_name);
}
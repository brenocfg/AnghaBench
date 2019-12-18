#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct cs_etm_traceid_queue {struct thread* thread; } ;
struct cs_etm_queue {TYPE_1__* etm; } ;
struct addr_location {TYPE_3__* map; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct TYPE_10__ {TYPE_2__ data; } ;
struct TYPE_9__ {TYPE_5__* dso; int /*<<< orphan*/  (* map_ip ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {struct thread* unknown_thread; struct machine* machine; } ;

/* Variables and functions */
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  DSO_DATA_STATUS_SEEN_ITRACE ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 scalar_t__ cs_etm__cpu_mode (struct cs_etm_queue*,int /*<<< orphan*/ ) ; 
 struct cs_etm_traceid_queue* cs_etm__etmq_get_traceid_queue (struct cs_etm_queue*,scalar_t__) ; 
 int dso__data_read_offset (TYPE_5__*,struct machine*,int /*<<< orphan*/ ,scalar_t__*,size_t) ; 
 scalar_t__ dso__data_status_seen (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__load (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,scalar_t__,int /*<<< orphan*/ ,struct addr_location*) ; 

__attribute__((used)) static u32 cs_etm__mem_access(struct cs_etm_queue *etmq, u8 trace_chan_id,
			      u64 address, size_t size, u8 *buffer)
{
	u8  cpumode;
	u64 offset;
	int len;
	struct thread *thread;
	struct machine *machine;
	struct addr_location al;
	struct cs_etm_traceid_queue *tidq;

	if (!etmq)
		return 0;

	machine = etmq->etm->machine;
	cpumode = cs_etm__cpu_mode(etmq, address);
	tidq = cs_etm__etmq_get_traceid_queue(etmq, trace_chan_id);
	if (!tidq)
		return 0;

	thread = tidq->thread;
	if (!thread) {
		if (cpumode != PERF_RECORD_MISC_KERNEL)
			return 0;
		thread = etmq->etm->unknown_thread;
	}

	if (!thread__find_map(thread, cpumode, address, &al) || !al.map->dso)
		return 0;

	if (al.map->dso->data.status == DSO_DATA_STATUS_ERROR &&
	    dso__data_status_seen(al.map->dso, DSO_DATA_STATUS_SEEN_ITRACE))
		return 0;

	offset = al.map->map_ip(al.map, address);

	map__load(al.map);

	len = dso__data_read_offset(al.map->dso, machine, offset, buffer, size);

	if (len <= 0)
		return 0;

	return len;
}
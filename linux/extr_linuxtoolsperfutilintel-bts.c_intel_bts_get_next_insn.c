#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u64 ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct intel_bts_queue {int /*<<< orphan*/  intel_pt_insn; int /*<<< orphan*/  tid; TYPE_1__* bts; } ;
struct addr_location {TYPE_2__* map; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_7__ {int is_64_bit; } ;
struct TYPE_6__ {TYPE_3__* dso; } ;
struct TYPE_5__ {struct machine* machine; } ;

/* Variables and functions */
 int INTEL_PT_INSN_BUF_SZ ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_KERNEL ; 
 int /*<<< orphan*/  PERF_RECORD_MISC_USER ; 
 scalar_t__ dso__data_read_addr (TYPE_3__*,TYPE_2__*,struct machine*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 scalar_t__ intel_pt_get_insn (unsigned char*,scalar_t__,int,int /*<<< orphan*/ *) ; 
 struct thread* machine__find_thread (struct machine*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ machine__kernel_ip (struct machine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__load (TYPE_2__*) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct addr_location*) ; 
 int /*<<< orphan*/  thread__put (struct thread*) ; 

__attribute__((used)) static int intel_bts_get_next_insn(struct intel_bts_queue *btsq, u64 ip)
{
	struct machine *machine = btsq->bts->machine;
	struct thread *thread;
	struct addr_location al;
	unsigned char buf[INTEL_PT_INSN_BUF_SZ];
	ssize_t len;
	int x86_64;
	uint8_t cpumode;
	int err = -1;

	if (machine__kernel_ip(machine, ip))
		cpumode = PERF_RECORD_MISC_KERNEL;
	else
		cpumode = PERF_RECORD_MISC_USER;

	thread = machine__find_thread(machine, -1, btsq->tid);
	if (!thread)
		return -1;

	if (!thread__find_map(thread, cpumode, ip, &al) || !al.map->dso)
		goto out_put;

	len = dso__data_read_addr(al.map->dso, al.map, machine, ip, buf,
				  INTEL_PT_INSN_BUF_SZ);
	if (len <= 0)
		goto out_put;

	/* Load maps to ensure dso->is_64_bit has been updated */
	map__load(al.map);

	x86_64 = al.map->dso->is_64_bit;

	if (intel_pt_get_insn(buf, len, x86_64, &btsq->intel_pt_insn))
		goto out_put;

	err = 0;
out_put:
	thread__put(thread);
	return err;
}
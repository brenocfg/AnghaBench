#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u64 ;
struct thread {int dummy; } ;
struct machine {int dummy; } ;
struct intel_pt_queue {TYPE_4__* pt; struct thread* thread; } ;
struct intel_pt_insn {scalar_t__ length; scalar_t__ branch; int /*<<< orphan*/  buf; int /*<<< orphan*/  rel; int /*<<< orphan*/  op; } ;
struct intel_pt_cache_entry {scalar_t__ insn_cnt; scalar_t__ byte_cnt; scalar_t__ branch; scalar_t__ length; int /*<<< orphan*/  insn; int /*<<< orphan*/  rel; int /*<<< orphan*/  op; } ;
struct addr_location {TYPE_2__* map; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_9__ {scalar_t__ status; } ;
struct TYPE_12__ {int is_64_bit; TYPE_1__ data; } ;
struct TYPE_11__ {struct thread* unknown_thread; struct machine* machine; } ;
struct TYPE_10__ {scalar_t__ (* map_ip ) (TYPE_2__*,scalar_t__) ;scalar_t__ end; TYPE_5__* dso; } ;

/* Variables and functions */
 scalar_t__ DSO_DATA_STATUS_ERROR ; 
 int /*<<< orphan*/  DSO_DATA_STATUS_SEEN_ITRACE ; 
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ INTEL_PT_BR_NO_BRANCH ; 
 int INTEL_PT_INSN_BUF_SZ ; 
 scalar_t__ PERF_RECORD_MISC_KERNEL ; 
 scalar_t__ dso__data_read_offset (TYPE_5__*,struct machine*,scalar_t__,unsigned char*,int) ; 
 scalar_t__ dso__data_status_seen (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pt_cache_add (TYPE_5__*,struct machine*,scalar_t__,scalar_t__,scalar_t__,struct intel_pt_insn*) ; 
 struct intel_pt_cache_entry* intel_pt_cache_lookup (TYPE_5__*,struct machine*,scalar_t__) ; 
 scalar_t__ intel_pt_cpumode (TYPE_4__*,scalar_t__) ; 
 scalar_t__ intel_pt_get_insn (unsigned char*,scalar_t__,int,struct intel_pt_insn*) ; 
 int /*<<< orphan*/  intel_pt_log_insn (struct intel_pt_insn*,scalar_t__) ; 
 int /*<<< orphan*/  intel_pt_log_insn_no_data (struct intel_pt_insn*,scalar_t__) ; 
 int /*<<< orphan*/  map__load (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  thread__find_map (struct thread*,scalar_t__,scalar_t__,struct addr_location*) ; 

__attribute__((used)) static int intel_pt_walk_next_insn(struct intel_pt_insn *intel_pt_insn,
				   uint64_t *insn_cnt_ptr, uint64_t *ip,
				   uint64_t to_ip, uint64_t max_insn_cnt,
				   void *data)
{
	struct intel_pt_queue *ptq = data;
	struct machine *machine = ptq->pt->machine;
	struct thread *thread;
	struct addr_location al;
	unsigned char buf[INTEL_PT_INSN_BUF_SZ];
	ssize_t len;
	int x86_64;
	u8 cpumode;
	u64 offset, start_offset, start_ip;
	u64 insn_cnt = 0;
	bool one_map = true;

	intel_pt_insn->length = 0;

	if (to_ip && *ip == to_ip)
		goto out_no_cache;

	cpumode = intel_pt_cpumode(ptq->pt, *ip);

	thread = ptq->thread;
	if (!thread) {
		if (cpumode != PERF_RECORD_MISC_KERNEL)
			return -EINVAL;
		thread = ptq->pt->unknown_thread;
	}

	while (1) {
		if (!thread__find_map(thread, cpumode, *ip, &al) || !al.map->dso)
			return -EINVAL;

		if (al.map->dso->data.status == DSO_DATA_STATUS_ERROR &&
		    dso__data_status_seen(al.map->dso,
					  DSO_DATA_STATUS_SEEN_ITRACE))
			return -ENOENT;

		offset = al.map->map_ip(al.map, *ip);

		if (!to_ip && one_map) {
			struct intel_pt_cache_entry *e;

			e = intel_pt_cache_lookup(al.map->dso, machine, offset);
			if (e &&
			    (!max_insn_cnt || e->insn_cnt <= max_insn_cnt)) {
				*insn_cnt_ptr = e->insn_cnt;
				*ip += e->byte_cnt;
				intel_pt_insn->op = e->op;
				intel_pt_insn->branch = e->branch;
				intel_pt_insn->length = e->length;
				intel_pt_insn->rel = e->rel;
				memcpy(intel_pt_insn->buf, e->insn,
				       INTEL_PT_INSN_BUF_SZ);
				intel_pt_log_insn_no_data(intel_pt_insn, *ip);
				return 0;
			}
		}

		start_offset = offset;
		start_ip = *ip;

		/* Load maps to ensure dso->is_64_bit has been updated */
		map__load(al.map);

		x86_64 = al.map->dso->is_64_bit;

		while (1) {
			len = dso__data_read_offset(al.map->dso, machine,
						    offset, buf,
						    INTEL_PT_INSN_BUF_SZ);
			if (len <= 0)
				return -EINVAL;

			if (intel_pt_get_insn(buf, len, x86_64, intel_pt_insn))
				return -EINVAL;

			intel_pt_log_insn(intel_pt_insn, *ip);

			insn_cnt += 1;

			if (intel_pt_insn->branch != INTEL_PT_BR_NO_BRANCH)
				goto out;

			if (max_insn_cnt && insn_cnt >= max_insn_cnt)
				goto out_no_cache;

			*ip += intel_pt_insn->length;

			if (to_ip && *ip == to_ip)
				goto out_no_cache;

			if (*ip >= al.map->end)
				break;

			offset += intel_pt_insn->length;
		}
		one_map = false;
	}
out:
	*insn_cnt_ptr = insn_cnt;

	if (!one_map)
		goto out_no_cache;

	/*
	 * Didn't lookup in the 'to_ip' case, so do it now to prevent duplicate
	 * entries.
	 */
	if (to_ip) {
		struct intel_pt_cache_entry *e;

		e = intel_pt_cache_lookup(al.map->dso, machine, start_offset);
		if (e)
			return 0;
	}

	/* Ignore cache errors */
	intel_pt_cache_add(al.map->dso, machine, start_offset, insn_cnt,
			   *ip - start_ip, intel_pt_insn);

	return 0;

out_no_cache:
	*insn_cnt_ptr = insn_cnt;
	return 0;
}
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
typedef  int /*<<< orphan*/  u64 ;
struct perf_env {scalar_t__ cpuid; } ;
struct ip_callchain {int dummy; } ;
struct intel_pt_queue {unsigned int queue_nr; int pid; int tid; int cpu; int next_tid; void* chain; void* last_branch_rb; void* last_branch; void* event_buf; int /*<<< orphan*/  decoder; int /*<<< orphan*/  exclude_kernel; struct intel_pt* pt; } ;
struct intel_pt_params {int period; int /*<<< orphan*/  flags; void* period_type; int /*<<< orphan*/  pgd_ip; int /*<<< orphan*/  tsc_ctc_ratio_d; int /*<<< orphan*/  tsc_ctc_ratio_n; int /*<<< orphan*/  mtc_period; int /*<<< orphan*/  max_non_turbo_ratio; int /*<<< orphan*/  branch_enable; int /*<<< orphan*/  return_compression; struct intel_pt_queue* data; int /*<<< orphan*/  lookahead; int /*<<< orphan*/  walk_insn; int /*<<< orphan*/  get_trace; } ;
struct TYPE_6__ {int callchain_sz; int last_branch_sz; int period; int period_type; scalar_t__ instructions; scalar_t__ last_branch; scalar_t__ callchain; } ;
struct TYPE_5__ {scalar_t__ cnt; } ;
struct intel_pt {TYPE_3__ synth_opts; TYPE_2__ filts; int /*<<< orphan*/  tsc_ctc_ratio_d; int /*<<< orphan*/  tsc_ctc_ratio_n; int /*<<< orphan*/  max_non_turbo_ratio; TYPE_1__* machine; } ;
struct branch_stack {int dummy; } ;
struct branch_entry {int dummy; } ;
struct TYPE_4__ {struct perf_env* env; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_FUP_WITH_NLIP ; 
 void* INTEL_PT_PERIOD_INSTRUCTIONS ; 
 void* INTEL_PT_PERIOD_TICKS ; 
#define  PERF_ITRACE_PERIOD_INSTRUCTIONS 130 
#define  PERF_ITRACE_PERIOD_NANOSECS 129 
#define  PERF_ITRACE_PERIOD_TICKS 128 
 int /*<<< orphan*/  PERF_SAMPLE_MAX_SIZE ; 
 int /*<<< orphan*/  free (struct intel_pt_queue*) ; 
 int /*<<< orphan*/  intel_pt_branch_enable (struct intel_pt*) ; 
 int /*<<< orphan*/  intel_pt_decoder_new (struct intel_pt_params*) ; 
 int /*<<< orphan*/  intel_pt_exclude_kernel (struct intel_pt*) ; 
 int /*<<< orphan*/  intel_pt_get_trace ; 
 int /*<<< orphan*/  intel_pt_lookahead ; 
 int /*<<< orphan*/  intel_pt_mtc_period (struct intel_pt*) ; 
 int intel_pt_ns_to_ticks (struct intel_pt*,int) ; 
 int /*<<< orphan*/  intel_pt_pgd_ip ; 
 int /*<<< orphan*/  intel_pt_return_compression (struct intel_pt*) ; 
 int /*<<< orphan*/  intel_pt_walk_next_insn ; 
 void* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (scalar_t__,char*,int) ; 
 void* zalloc (size_t) ; 
 int /*<<< orphan*/  zfree (void**) ; 

__attribute__((used)) static struct intel_pt_queue *intel_pt_alloc_queue(struct intel_pt *pt,
						   unsigned int queue_nr)
{
	struct intel_pt_params params = { .get_trace = 0, };
	struct perf_env *env = pt->machine->env;
	struct intel_pt_queue *ptq;

	ptq = zalloc(sizeof(struct intel_pt_queue));
	if (!ptq)
		return NULL;

	if (pt->synth_opts.callchain) {
		size_t sz = sizeof(struct ip_callchain);

		/* Add 1 to callchain_sz for callchain context */
		sz += (pt->synth_opts.callchain_sz + 1) * sizeof(u64);
		ptq->chain = zalloc(sz);
		if (!ptq->chain)
			goto out_free;
	}

	if (pt->synth_opts.last_branch) {
		size_t sz = sizeof(struct branch_stack);

		sz += pt->synth_opts.last_branch_sz *
		      sizeof(struct branch_entry);
		ptq->last_branch = zalloc(sz);
		if (!ptq->last_branch)
			goto out_free;
		ptq->last_branch_rb = zalloc(sz);
		if (!ptq->last_branch_rb)
			goto out_free;
	}

	ptq->event_buf = malloc(PERF_SAMPLE_MAX_SIZE);
	if (!ptq->event_buf)
		goto out_free;

	ptq->pt = pt;
	ptq->queue_nr = queue_nr;
	ptq->exclude_kernel = intel_pt_exclude_kernel(pt);
	ptq->pid = -1;
	ptq->tid = -1;
	ptq->cpu = -1;
	ptq->next_tid = -1;

	params.get_trace = intel_pt_get_trace;
	params.walk_insn = intel_pt_walk_next_insn;
	params.lookahead = intel_pt_lookahead;
	params.data = ptq;
	params.return_compression = intel_pt_return_compression(pt);
	params.branch_enable = intel_pt_branch_enable(pt);
	params.max_non_turbo_ratio = pt->max_non_turbo_ratio;
	params.mtc_period = intel_pt_mtc_period(pt);
	params.tsc_ctc_ratio_n = pt->tsc_ctc_ratio_n;
	params.tsc_ctc_ratio_d = pt->tsc_ctc_ratio_d;

	if (pt->filts.cnt > 0)
		params.pgd_ip = intel_pt_pgd_ip;

	if (pt->synth_opts.instructions) {
		if (pt->synth_opts.period) {
			switch (pt->synth_opts.period_type) {
			case PERF_ITRACE_PERIOD_INSTRUCTIONS:
				params.period_type =
						INTEL_PT_PERIOD_INSTRUCTIONS;
				params.period = pt->synth_opts.period;
				break;
			case PERF_ITRACE_PERIOD_TICKS:
				params.period_type = INTEL_PT_PERIOD_TICKS;
				params.period = pt->synth_opts.period;
				break;
			case PERF_ITRACE_PERIOD_NANOSECS:
				params.period_type = INTEL_PT_PERIOD_TICKS;
				params.period = intel_pt_ns_to_ticks(pt,
							pt->synth_opts.period);
				break;
			default:
				break;
			}
		}

		if (!params.period) {
			params.period_type = INTEL_PT_PERIOD_INSTRUCTIONS;
			params.period = 1;
		}
	}

	if (env->cpuid && !strncmp(env->cpuid, "GenuineIntel,6,92,", 18))
		params.flags |= INTEL_PT_FUP_WITH_NLIP;

	ptq->decoder = intel_pt_decoder_new(&params);
	if (!ptq->decoder)
		goto out_free;

	return ptq;

out_free:
	zfree(&ptq->event_buf);
	zfree(&ptq->last_branch);
	zfree(&ptq->last_branch_rb);
	zfree(&ptq->chain);
	free(ptq);
	return NULL;
}
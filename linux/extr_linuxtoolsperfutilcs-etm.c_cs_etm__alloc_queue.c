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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/  reg_traceidr; int /*<<< orphan*/  reg_configr; int /*<<< orphan*/  reg_idr8; int /*<<< orphan*/  reg_idr2; int /*<<< orphan*/  reg_idr1; int /*<<< orphan*/  reg_idr0; } ;
struct cs_etm_trace_params {TYPE_2__ etmv4; int /*<<< orphan*/  protocol; } ;
struct cs_etm_queue {unsigned int queue_nr; int pid; int tid; int cpu; struct cs_etm_trace_params* packet; struct cs_etm_trace_params* prev_packet; struct cs_etm_trace_params* last_branch_rb; struct cs_etm_trace_params* last_branch; struct cs_etm_trace_params* event_buf; int /*<<< orphan*/  decoder; scalar_t__ period_instructions; scalar_t__ offset; struct cs_etm_auxtrace* etm; } ;
struct cs_etm_packet {int dummy; } ;
struct cs_etm_decoder_params {int formatted; int fsyncs; int hsyncs; int frame_aligned; struct cs_etm_queue* data; int /*<<< orphan*/  operation; int /*<<< orphan*/  packet_printer; } ;
struct TYPE_3__ {int last_branch_sz; scalar_t__ last_branch; } ;
struct cs_etm_auxtrace {int num_cpu; int /*<<< orphan*/ ** metadata; TYPE_1__ synth_opts; scalar_t__ sample_branches; } ;
struct branch_stack {int dummy; } ;
struct branch_entry {int dummy; } ;

/* Variables and functions */
 size_t CS_ETMV4_TRCCONFIGR ; 
 size_t CS_ETMV4_TRCIDR0 ; 
 size_t CS_ETMV4_TRCIDR1 ; 
 size_t CS_ETMV4_TRCIDR2 ; 
 size_t CS_ETMV4_TRCIDR8 ; 
 size_t CS_ETMV4_TRCTRACEIDR ; 
 int /*<<< orphan*/  CS_ETM_OPERATION_DECODE ; 
 int /*<<< orphan*/  CS_ETM_PROTO_ETMV4i ; 
 int /*<<< orphan*/  PERF_SAMPLE_MAX_SIZE ; 
 int /*<<< orphan*/  cs_etm__mem_access ; 
 int /*<<< orphan*/  cs_etm__packet_dump ; 
 scalar_t__ cs_etm_decoder__add_mem_access_cb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm_decoder__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm_decoder__new (int,struct cs_etm_decoder_params*,struct cs_etm_trace_params*) ; 
 int /*<<< orphan*/  free (struct cs_etm_queue*) ; 
 struct cs_etm_trace_params* malloc (int /*<<< orphan*/ ) ; 
 void* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct cs_etm_trace_params**) ; 

__attribute__((used)) static struct cs_etm_queue *cs_etm__alloc_queue(struct cs_etm_auxtrace *etm,
						unsigned int queue_nr)
{
	int i;
	struct cs_etm_decoder_params d_params;
	struct cs_etm_trace_params  *t_params;
	struct cs_etm_queue *etmq;
	size_t szp = sizeof(struct cs_etm_packet);

	etmq = zalloc(sizeof(*etmq));
	if (!etmq)
		return NULL;

	etmq->packet = zalloc(szp);
	if (!etmq->packet)
		goto out_free;

	if (etm->synth_opts.last_branch || etm->sample_branches) {
		etmq->prev_packet = zalloc(szp);
		if (!etmq->prev_packet)
			goto out_free;
	}

	if (etm->synth_opts.last_branch) {
		size_t sz = sizeof(struct branch_stack);

		sz += etm->synth_opts.last_branch_sz *
		      sizeof(struct branch_entry);
		etmq->last_branch = zalloc(sz);
		if (!etmq->last_branch)
			goto out_free;
		etmq->last_branch_rb = zalloc(sz);
		if (!etmq->last_branch_rb)
			goto out_free;
	}

	etmq->event_buf = malloc(PERF_SAMPLE_MAX_SIZE);
	if (!etmq->event_buf)
		goto out_free;

	etmq->etm = etm;
	etmq->queue_nr = queue_nr;
	etmq->pid = -1;
	etmq->tid = -1;
	etmq->cpu = -1;

	/* Use metadata to fill in trace parameters for trace decoder */
	t_params = zalloc(sizeof(*t_params) * etm->num_cpu);

	if (!t_params)
		goto out_free;

	for (i = 0; i < etm->num_cpu; i++) {
		t_params[i].protocol = CS_ETM_PROTO_ETMV4i;
		t_params[i].etmv4.reg_idr0 = etm->metadata[i][CS_ETMV4_TRCIDR0];
		t_params[i].etmv4.reg_idr1 = etm->metadata[i][CS_ETMV4_TRCIDR1];
		t_params[i].etmv4.reg_idr2 = etm->metadata[i][CS_ETMV4_TRCIDR2];
		t_params[i].etmv4.reg_idr8 = etm->metadata[i][CS_ETMV4_TRCIDR8];
		t_params[i].etmv4.reg_configr =
					etm->metadata[i][CS_ETMV4_TRCCONFIGR];
		t_params[i].etmv4.reg_traceidr =
					etm->metadata[i][CS_ETMV4_TRCTRACEIDR];
	}

	/* Set decoder parameters to simply print the trace packets */
	d_params.packet_printer = cs_etm__packet_dump;
	d_params.operation = CS_ETM_OPERATION_DECODE;
	d_params.formatted = true;
	d_params.fsyncs = false;
	d_params.hsyncs = false;
	d_params.frame_aligned = true;
	d_params.data = etmq;

	etmq->decoder = cs_etm_decoder__new(etm->num_cpu, &d_params, t_params);

	zfree(&t_params);

	if (!etmq->decoder)
		goto out_free;

	/*
	 * Register a function to handle all memory accesses required by
	 * the trace decoder library.
	 */
	if (cs_etm_decoder__add_mem_access_cb(etmq->decoder,
					      0x0L, ((u64) -1L),
					      cs_etm__mem_access))
		goto out_free_decoder;

	etmq->offset = 0;
	etmq->period_instructions = 0;

	return etmq;

out_free_decoder:
	cs_etm_decoder__free(etmq->decoder);
out_free:
	zfree(&etmq->event_buf);
	zfree(&etmq->last_branch);
	zfree(&etmq->last_branch_rb);
	zfree(&etmq->prev_packet);
	zfree(&etmq->packet);
	free(etmq);

	return NULL;
}
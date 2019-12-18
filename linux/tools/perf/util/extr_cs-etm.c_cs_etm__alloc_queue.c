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
typedef  int /*<<< orphan*/  u64 ;
struct cs_etm_trace_params {int dummy; } ;
struct cs_etm_queue {int /*<<< orphan*/  traceid_queues_list; int /*<<< orphan*/  decoder; } ;
struct cs_etm_decoder_params {int dummy; } ;
struct cs_etm_auxtrace {int num_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_OPERATION_DECODE ; 
 scalar_t__ cs_etm__init_decoder_params (struct cs_etm_decoder_params*,struct cs_etm_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ cs_etm__init_trace_params (struct cs_etm_trace_params*,struct cs_etm_auxtrace*) ; 
 int /*<<< orphan*/  cs_etm__mem_access ; 
 scalar_t__ cs_etm_decoder__add_mem_access_cb (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm_decoder__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs_etm_decoder__new (int,struct cs_etm_decoder_params*,struct cs_etm_trace_params*) ; 
 int /*<<< orphan*/  free (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  intlist__delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intlist__new (int /*<<< orphan*/ *) ; 
 void* zalloc (int) ; 
 int /*<<< orphan*/  zfree (struct cs_etm_trace_params**) ; 

__attribute__((used)) static struct cs_etm_queue *cs_etm__alloc_queue(struct cs_etm_auxtrace *etm)
{
	struct cs_etm_decoder_params d_params;
	struct cs_etm_trace_params  *t_params = NULL;
	struct cs_etm_queue *etmq;

	etmq = zalloc(sizeof(*etmq));
	if (!etmq)
		return NULL;

	etmq->traceid_queues_list = intlist__new(NULL);
	if (!etmq->traceid_queues_list)
		goto out_free;

	/* Use metadata to fill in trace parameters for trace decoder */
	t_params = zalloc(sizeof(*t_params) * etm->num_cpu);

	if (!t_params)
		goto out_free;

	if (cs_etm__init_trace_params(t_params, etm))
		goto out_free;

	/* Set decoder parameters to decode trace packets */
	if (cs_etm__init_decoder_params(&d_params, etmq,
					CS_ETM_OPERATION_DECODE))
		goto out_free;

	etmq->decoder = cs_etm_decoder__new(etm->num_cpu, &d_params, t_params);

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

	zfree(&t_params);
	return etmq;

out_free_decoder:
	cs_etm_decoder__free(etmq->decoder);
out_free:
	intlist__delete(etmq->traceid_queues_list);
	free(etmq);

	return NULL;
}
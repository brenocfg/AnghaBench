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
typedef  int /*<<< orphan*/  u8 ;
struct intlist {int dummy; } ;
struct int_node {void* priv; } ;
struct cs_etm_traceid_queue {int dummy; } ;
struct cs_etm_queue {struct cs_etm_traceid_queue** traceid_queues; struct intlist* traceid_queues_list; struct cs_etm_auxtrace* etm; } ;
struct cs_etm_auxtrace {scalar_t__ timeless_decoding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_ETM_PER_THREAD_TRACEID ; 
 scalar_t__ cs_etm__init_traceid_queue (struct cs_etm_queue*,struct cs_etm_traceid_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cs_etm_traceid_queue*) ; 
 struct int_node* intlist__find (struct intlist*,int /*<<< orphan*/ ) ; 
 struct int_node* intlist__findnew (struct intlist*,int /*<<< orphan*/ ) ; 
 int intlist__nr_entries (struct intlist*) ; 
 int /*<<< orphan*/  intlist__remove (struct intlist*,struct int_node*) ; 
 struct cs_etm_traceid_queue* malloc (int) ; 
 int /*<<< orphan*/  memset (struct cs_etm_traceid_queue*,int /*<<< orphan*/ ,int) ; 
 struct cs_etm_traceid_queue** reallocarray (struct cs_etm_traceid_queue**,int,int) ; 

__attribute__((used)) static struct cs_etm_traceid_queue
*cs_etm__etmq_get_traceid_queue(struct cs_etm_queue *etmq, u8 trace_chan_id)
{
	int idx;
	struct int_node *inode;
	struct intlist *traceid_queues_list;
	struct cs_etm_traceid_queue *tidq, **traceid_queues;
	struct cs_etm_auxtrace *etm = etmq->etm;

	if (etm->timeless_decoding)
		trace_chan_id = CS_ETM_PER_THREAD_TRACEID;

	traceid_queues_list = etmq->traceid_queues_list;

	/*
	 * Check if the traceid_queue exist for this traceID by looking
	 * in the queue list.
	 */
	inode = intlist__find(traceid_queues_list, trace_chan_id);
	if (inode) {
		idx = (int)(intptr_t)inode->priv;
		return etmq->traceid_queues[idx];
	}

	/* We couldn't find a traceid_queue for this traceID, allocate one */
	tidq = malloc(sizeof(*tidq));
	if (!tidq)
		return NULL;

	memset(tidq, 0, sizeof(*tidq));

	/* Get a valid index for the new traceid_queue */
	idx = intlist__nr_entries(traceid_queues_list);
	/* Memory for the inode is free'ed in cs_etm_free_traceid_queues () */
	inode = intlist__findnew(traceid_queues_list, trace_chan_id);
	if (!inode)
		goto out_free;

	/* Associate this traceID with this index */
	inode->priv = (void *)(intptr_t)idx;

	if (cs_etm__init_traceid_queue(etmq, tidq, trace_chan_id))
		goto out_free;

	/* Grow the traceid_queues array by one unit */
	traceid_queues = etmq->traceid_queues;
	traceid_queues = reallocarray(traceid_queues,
				      idx + 1,
				      sizeof(*traceid_queues));

	/*
	 * On failure reallocarray() returns NULL and the original block of
	 * memory is left untouched.
	 */
	if (!traceid_queues)
		goto out_free;

	traceid_queues[idx] = tidq;
	etmq->traceid_queues = traceid_queues;

	return etmq->traceid_queues[idx];

out_free:
	/*
	 * Function intlist__remove() removes the inode from the list
	 * and delete the memory associated to it.
	 */
	intlist__remove(traceid_queues_list, inode);
	free(tidq);

	return NULL;
}
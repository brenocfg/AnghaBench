#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  shm_mq_handle ;
typedef  int /*<<< orphan*/  shm_mq ;
struct TYPE_3__ {int nworkers; int /*<<< orphan*/  toc; int /*<<< orphan*/  seg; } ;
typedef  int Size ;
typedef  TYPE_1__ ParallelContext ;

/* Variables and functions */
 int /*<<< orphan*/  MyProc ; 
 int /*<<< orphan*/  PARALLEL_KEY_TUPLE_QUEUE ; 
 int PARALLEL_TUPLE_QUEUE_SIZE ; 
 int /*<<< orphan*/  mul_size (int,int) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/ * shm_mq_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * shm_mq_create (char*,int) ; 
 int /*<<< orphan*/  shm_mq_set_receiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* shm_toc_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* shm_toc_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static shm_mq_handle **
ExecParallelSetupTupleQueues(ParallelContext *pcxt, bool reinitialize)
{
	shm_mq_handle **responseq;
	char	   *tqueuespace;
	int			i;

	/* Skip this if no workers. */
	if (pcxt->nworkers == 0)
		return NULL;

	/* Allocate memory for shared memory queue handles. */
	responseq = (shm_mq_handle **)
		palloc(pcxt->nworkers * sizeof(shm_mq_handle *));

	/*
	 * If not reinitializing, allocate space from the DSM for the queues;
	 * otherwise, find the already allocated space.
	 */
	if (!reinitialize)
		tqueuespace =
			shm_toc_allocate(pcxt->toc,
							 mul_size(PARALLEL_TUPLE_QUEUE_SIZE,
									  pcxt->nworkers));
	else
		tqueuespace = shm_toc_lookup(pcxt->toc, PARALLEL_KEY_TUPLE_QUEUE, false);

	/* Create the queues, and become the receiver for each. */
	for (i = 0; i < pcxt->nworkers; ++i)
	{
		shm_mq	   *mq;

		mq = shm_mq_create(tqueuespace +
						   ((Size) i) * PARALLEL_TUPLE_QUEUE_SIZE,
						   (Size) PARALLEL_TUPLE_QUEUE_SIZE);

		shm_mq_set_receiver(mq, MyProc);
		responseq[i] = shm_mq_attach(mq, pcxt->seg, NULL);
	}

	/* Add array of queues to shm_toc, so others can find it. */
	if (!reinitialize)
		shm_toc_insert(pcxt->toc, PARALLEL_KEY_TUPLE_QUEUE, tqueuespace);

	/* Return array of handles. */
	return responseq;
}
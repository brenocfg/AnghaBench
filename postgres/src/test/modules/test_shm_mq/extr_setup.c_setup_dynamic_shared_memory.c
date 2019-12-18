#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_12__ {int workers_total; scalar_t__ workers_ready; scalar_t__ workers_attached; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ test_shm_mq_header ;
typedef  int /*<<< orphan*/  shm_toc_estimator ;
typedef  int /*<<< orphan*/  shm_toc ;
typedef  TYPE_1__ shm_mq ;
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  scalar_t__ Size ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MyProc ; 
 int /*<<< orphan*/  PG_TEST_SHM_MQ_MAGIC ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dsm_create (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsm_segment_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 TYPE_1__* shm_mq_create (TYPE_1__*,scalar_t__) ; 
 scalar_t__ shm_mq_minimum_size ; 
 int /*<<< orphan*/  shm_mq_set_receiver (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_mq_set_sender (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* shm_toc_allocate (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * shm_toc_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ shm_toc_estimate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_toc_estimate_chunk (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  shm_toc_estimate_keys (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shm_toc_initialize_estimator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_toc_insert (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static void
setup_dynamic_shared_memory(int64 queue_size, int nworkers,
							dsm_segment **segp, test_shm_mq_header **hdrp,
							shm_mq **outp, shm_mq **inp)
{
	shm_toc_estimator e;
	int			i;
	Size		segsize;
	dsm_segment *seg;
	shm_toc    *toc;
	test_shm_mq_header *hdr;

	/* Ensure a valid queue size. */
	if (queue_size < 0 || ((uint64) queue_size) < shm_mq_minimum_size)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("queue size must be at least %zu bytes",
						shm_mq_minimum_size)));
	if (queue_size != ((Size) queue_size))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("queue size overflows size_t")));

	/*
	 * Estimate how much shared memory we need.
	 *
	 * Because the TOC machinery may choose to insert padding of oddly-sized
	 * requests, we must estimate each chunk separately.
	 *
	 * We need one key to register the location of the header, and we need
	 * nworkers + 1 keys to track the locations of the message queues.
	 */
	shm_toc_initialize_estimator(&e);
	shm_toc_estimate_chunk(&e, sizeof(test_shm_mq_header));
	for (i = 0; i <= nworkers; ++i)
		shm_toc_estimate_chunk(&e, (Size) queue_size);
	shm_toc_estimate_keys(&e, 2 + nworkers);
	segsize = shm_toc_estimate(&e);

	/* Create the shared memory segment and establish a table of contents. */
	seg = dsm_create(shm_toc_estimate(&e), 0);
	toc = shm_toc_create(PG_TEST_SHM_MQ_MAGIC, dsm_segment_address(seg),
						 segsize);

	/* Set up the header region. */
	hdr = shm_toc_allocate(toc, sizeof(test_shm_mq_header));
	SpinLockInit(&hdr->mutex);
	hdr->workers_total = nworkers;
	hdr->workers_attached = 0;
	hdr->workers_ready = 0;
	shm_toc_insert(toc, 0, hdr);

	/* Set up one message queue per worker, plus one. */
	for (i = 0; i <= nworkers; ++i)
	{
		shm_mq	   *mq;

		mq = shm_mq_create(shm_toc_allocate(toc, (Size) queue_size),
						   (Size) queue_size);
		shm_toc_insert(toc, i + 1, mq);

		if (i == 0)
		{
			/* We send messages to the first queue. */
			shm_mq_set_sender(mq, MyProc);
			*outp = mq;
		}
		if (i == nworkers)
		{
			/* We receive messages from the last queue. */
			shm_mq_set_receiver(mq, MyProc);
			*inp = mq;
		}
	}

	/* Return results to caller. */
	*segp = seg;
	*hdrp = hdr;
}
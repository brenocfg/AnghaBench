#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ format; int indent; int /*<<< orphan*/  str; } ;
struct TYPE_11__ {scalar_t__ nbatch; long nbuckets; long nbuckets_original; long nbatch_original; scalar_t__ space_peak; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__* shared_info; int /*<<< orphan*/  hashtable; } ;
struct TYPE_9__ {int num_workers; TYPE_3__* hinstrument; } ;
typedef  TYPE_1__ SharedHashInfo ;
typedef  TYPE_2__ HashState ;
typedef  TYPE_3__ HashInstrumentation ;
typedef  TYPE_4__ ExplainState ;

/* Variables and functions */
 scalar_t__ EXPLAIN_FORMAT_TEXT ; 
 int /*<<< orphan*/  ExecHashGetInstrumentation (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExplainPropertyInteger (char*,char*,long,TYPE_4__*) ; 
 void* Max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,long,...) ; 
 int /*<<< orphan*/  appendStringInfoSpaces (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
show_hash_info(HashState *hashstate, ExplainState *es)
{
	HashInstrumentation hinstrument = {0};

	/*
	 * In a parallel query, the leader process may or may not have run the
	 * hash join, and even if it did it may not have built a hash table due to
	 * timing (if it started late it might have seen no tuples in the outer
	 * relation and skipped building the hash table).  Therefore we have to be
	 * prepared to get instrumentation data from all participants.
	 */
	if (hashstate->hashtable)
		ExecHashGetInstrumentation(&hinstrument, hashstate->hashtable);

	/*
	 * Merge results from workers.  In the parallel-oblivious case, the
	 * results from all participants should be identical, except where
	 * participants didn't run the join at all so have no data.  In the
	 * parallel-aware case, we need to consider all the results.  Each worker
	 * may have seen a different subset of batches and we want to find the
	 * highest memory usage for any one batch across all batches.
	 */
	if (hashstate->shared_info)
	{
		SharedHashInfo *shared_info = hashstate->shared_info;
		int			i;

		for (i = 0; i < shared_info->num_workers; ++i)
		{
			HashInstrumentation *worker_hi = &shared_info->hinstrument[i];

			if (worker_hi->nbatch > 0)
			{
				/*
				 * Every participant should agree on the buckets, so to be
				 * sure we have a value we'll just overwrite each time.
				 */
				hinstrument.nbuckets = worker_hi->nbuckets;
				hinstrument.nbuckets_original = worker_hi->nbuckets_original;

				/*
				 * Normally every participant should agree on the number of
				 * batches too, but it's possible for a backend that started
				 * late and missed the whole join not to have the final nbatch
				 * number.  So we'll take the largest number.
				 */
				hinstrument.nbatch = Max(hinstrument.nbatch, worker_hi->nbatch);
				hinstrument.nbatch_original = worker_hi->nbatch_original;

				/*
				 * In a parallel-aware hash join, for now we report the
				 * maximum peak memory reported by any worker.
				 */
				hinstrument.space_peak =
					Max(hinstrument.space_peak, worker_hi->space_peak);
			}
		}
	}

	if (hinstrument.nbatch > 0)
	{
		long		spacePeakKb = (hinstrument.space_peak + 1023) / 1024;

		if (es->format != EXPLAIN_FORMAT_TEXT)
		{
			ExplainPropertyInteger("Hash Buckets", NULL,
								   hinstrument.nbuckets, es);
			ExplainPropertyInteger("Original Hash Buckets", NULL,
								   hinstrument.nbuckets_original, es);
			ExplainPropertyInteger("Hash Batches", NULL,
								   hinstrument.nbatch, es);
			ExplainPropertyInteger("Original Hash Batches", NULL,
								   hinstrument.nbatch_original, es);
			ExplainPropertyInteger("Peak Memory Usage", "kB",
								   spacePeakKb, es);
		}
		else if (hinstrument.nbatch_original != hinstrument.nbatch ||
				 hinstrument.nbuckets_original != hinstrument.nbuckets)
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfo(es->str,
							 "Buckets: %d (originally %d)  Batches: %d (originally %d)  Memory Usage: %ldkB\n",
							 hinstrument.nbuckets,
							 hinstrument.nbuckets_original,
							 hinstrument.nbatch,
							 hinstrument.nbatch_original,
							 spacePeakKb);
		}
		else
		{
			appendStringInfoSpaces(es->str, es->indent * 2);
			appendStringInfo(es->str,
							 "Buckets: %d  Batches: %d  Memory Usage: %ldkB\n",
							 hinstrument.nbuckets, hinstrument.nbatch,
							 spacePeakKb);
		}
	}
}
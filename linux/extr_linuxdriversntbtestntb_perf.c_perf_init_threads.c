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
struct perf_thread {int tidx; int /*<<< orphan*/  work; int /*<<< orphan*/  dma_wait; int /*<<< orphan*/  status; struct perf_ctx* perf; } ;
struct perf_ctx {struct perf_thread* threads; int /*<<< orphan*/  twait; int /*<<< orphan*/ * peers; int /*<<< orphan*/ * test_peer; int /*<<< orphan*/  tcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_THREADS_CNT ; 
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_THREADS_CNT ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_thread_work ; 

__attribute__((used)) static void perf_init_threads(struct perf_ctx *perf)
{
	struct perf_thread *pthr;
	int tidx;

	perf->tcnt = DEF_THREADS_CNT;
	perf->test_peer = &perf->peers[0];
	init_waitqueue_head(&perf->twait);

	for (tidx = 0; tidx < MAX_THREADS_CNT; tidx++) {
		pthr = &perf->threads[tidx];

		pthr->perf = perf;
		pthr->tidx = tidx;
		pthr->status = -ENODATA;
		init_waitqueue_head(&pthr->dma_wait);
		INIT_WORK(&pthr->work, perf_thread_work);
	}
}
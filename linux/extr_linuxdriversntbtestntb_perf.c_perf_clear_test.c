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
struct perf_thread {int /*<<< orphan*/  src; int /*<<< orphan*/  dma_chan; struct perf_ctx* perf; } ;
struct perf_ctx {int /*<<< orphan*/  twait; int /*<<< orphan*/  tsync; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_dma ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_clear_test(struct perf_thread *pthr)
{
	struct perf_ctx *perf = pthr->perf;

	if (!use_dma)
		goto no_dma_notify;

	/*
	 * If test finished without errors, termination isn't needed.
	 * We call it anyway just to be sure of the transfers completion.
	 */
	(void)dmaengine_terminate_sync(pthr->dma_chan);

	dma_release_channel(pthr->dma_chan);

no_dma_notify:
	atomic_dec(&perf->tsync);
	wake_up(&perf->twait);
	kfree(pthr->src);
}
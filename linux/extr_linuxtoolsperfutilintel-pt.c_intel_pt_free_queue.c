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
struct intel_pt_queue {int /*<<< orphan*/  chain; int /*<<< orphan*/  last_branch_rb; int /*<<< orphan*/  last_branch; int /*<<< orphan*/  event_buf; int /*<<< orphan*/  decoder; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct intel_pt_queue*) ; 
 int /*<<< orphan*/  intel_pt_decoder_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pt_free_queue(void *priv)
{
	struct intel_pt_queue *ptq = priv;

	if (!ptq)
		return;
	thread__zput(ptq->thread);
	intel_pt_decoder_free(ptq->decoder);
	zfree(&ptq->event_buf);
	zfree(&ptq->last_branch);
	zfree(&ptq->last_branch_rb);
	zfree(&ptq->chain);
	free(ptq);
}
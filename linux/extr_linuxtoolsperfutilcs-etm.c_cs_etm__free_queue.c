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
struct cs_etm_queue {int /*<<< orphan*/  packet; int /*<<< orphan*/  prev_packet; int /*<<< orphan*/  last_branch_rb; int /*<<< orphan*/  last_branch; int /*<<< orphan*/  event_buf; int /*<<< orphan*/  decoder; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_etm_decoder__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cs_etm_queue*) ; 
 int /*<<< orphan*/  thread__zput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cs_etm__free_queue(void *priv)
{
	struct cs_etm_queue *etmq = priv;

	if (!etmq)
		return;

	thread__zput(etmq->thread);
	cs_etm_decoder__free(etmq->decoder);
	zfree(&etmq->event_buf);
	zfree(&etmq->last_branch);
	zfree(&etmq->last_branch_rb);
	zfree(&etmq->prev_packet);
	zfree(&etmq->packet);
	free(etmq);
}
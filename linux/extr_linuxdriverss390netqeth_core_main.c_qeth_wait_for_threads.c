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
struct qeth_card {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 scalar_t__ qeth_is_recovery_task (struct qeth_card*) ; 
 scalar_t__ qeth_threads_running (struct qeth_card*,unsigned long) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

int qeth_wait_for_threads(struct qeth_card *card, unsigned long threads)
{
	if (qeth_is_recovery_task(card))
		return 0;
	return wait_event_interruptible(card->wait_q,
			qeth_threads_running(card, threads) == 0);
}
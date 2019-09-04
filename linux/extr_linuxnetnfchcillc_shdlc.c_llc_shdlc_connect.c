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
struct llc_shdlc {int connect_result; int /*<<< orphan*/  sm_work; int /*<<< orphan*/  state_mutex; scalar_t__ connect_tries; int /*<<< orphan*/ * connect_wq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_WAIT_QUEUE_HEAD_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHDLC_CONNECTING ; 
 int /*<<< orphan*/  connect_wq ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int llc_shdlc_connect(struct llc_shdlc *shdlc)
{
	DECLARE_WAIT_QUEUE_HEAD_ONSTACK(connect_wq);

	pr_debug("\n");

	mutex_lock(&shdlc->state_mutex);

	shdlc->state = SHDLC_CONNECTING;
	shdlc->connect_wq = &connect_wq;
	shdlc->connect_tries = 0;
	shdlc->connect_result = 1;

	mutex_unlock(&shdlc->state_mutex);

	schedule_work(&shdlc->sm_work);

	wait_event(connect_wq, shdlc->connect_result != 1);

	return shdlc->connect_result;
}
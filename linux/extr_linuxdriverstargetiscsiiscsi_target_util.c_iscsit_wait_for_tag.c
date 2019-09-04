#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct sbq_wait_state* ws; } ;
struct se_session {TYPE_1__ sess_tag_pool; } ;
struct sbq_wait_state {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int TASK_RUNNING ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int sbitmap_queue_get (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ signal_pending_state (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int iscsit_wait_for_tag(struct se_session *se_sess, int state, int *cpup)
{
	int tag = -1;
	DEFINE_WAIT(wait);
	struct sbq_wait_state *ws;

	if (state == TASK_RUNNING)
		return tag;

	ws = &se_sess->sess_tag_pool.ws[0];
	for (;;) {
		prepare_to_wait_exclusive(&ws->wait, &wait, state);
		if (signal_pending_state(state, current))
			break;
		tag = sbitmap_queue_get(&se_sess->sess_tag_pool, cpup);
		if (tag >= 0)
			break;
		schedule();
	}

	finish_wait(&ws->wait, &wait);
	return tag;
}
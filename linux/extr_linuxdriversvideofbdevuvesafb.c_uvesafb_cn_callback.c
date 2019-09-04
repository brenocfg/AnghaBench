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
struct uvesafb_task {int buf_len; } ;
struct TYPE_2__ {int buf_len; } ;
struct uvesafb_ktask {scalar_t__ ack; int /*<<< orphan*/  done; TYPE_1__ t; TYPE_1__* buf; } ;
struct netlink_skb_parms {int dummy; } ;
struct cn_msg {size_t seq; scalar_t__ ack; int len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t UVESAFB_TASKS_MAX ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct uvesafb_task*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvfb_lock ; 
 struct uvesafb_ktask** uvfb_tasks ; 

__attribute__((used)) static void uvesafb_cn_callback(struct cn_msg *msg, struct netlink_skb_parms *nsp)
{
	struct uvesafb_task *utask;
	struct uvesafb_ktask *task;

	if (!capable(CAP_SYS_ADMIN))
		return;

	if (msg->seq >= UVESAFB_TASKS_MAX)
		return;

	mutex_lock(&uvfb_lock);
	task = uvfb_tasks[msg->seq];

	if (!task || msg->ack != task->ack) {
		mutex_unlock(&uvfb_lock);
		return;
	}

	utask = (struct uvesafb_task *)msg->data;

	/* Sanity checks for the buffer length. */
	if (task->t.buf_len < utask->buf_len ||
	    utask->buf_len > msg->len - sizeof(*utask)) {
		mutex_unlock(&uvfb_lock);
		return;
	}

	uvfb_tasks[msg->seq] = NULL;
	mutex_unlock(&uvfb_lock);

	memcpy(&task->t, utask, sizeof(*utask));

	if (task->t.buf_len && task->buf)
		memcpy(task->buf, utask + 1, task->t.buf_len);

	complete(task->done);
	return;
}
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
typedef  int /*<<< orphan*/  u32 ;
struct mixart_msg {int dummy; } ;
struct mixart_mgr {int /*<<< orphan*/  msg_processed; int /*<<< orphan*/  msg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int send_msg (struct mixart_mgr*,struct mixart_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int snd_mixart_send_msg_nonblock(struct mixart_mgr *mgr, struct mixart_msg *request)
{
	u32 message_frame;
	int err;

	/* just send the message (do not mark it as a pending one) */
	mutex_lock(&mgr->msg_lock);
	err = send_msg(mgr, request, MSG_DEFAULT_SIZE, 0, &message_frame);
	mutex_unlock(&mgr->msg_lock);

	/* the answer will be handled by snd_struct mixart_msgasklet()  */
	atomic_inc(&mgr->msg_processed);

	return err;
}
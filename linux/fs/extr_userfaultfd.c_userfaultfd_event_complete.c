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
struct TYPE_2__ {scalar_t__ event; } ;
struct userfaultfd_wait_queue {int /*<<< orphan*/  wq; TYPE_1__ msg; } ;
struct userfaultfd_ctx {int /*<<< orphan*/  event_wqh; } ;

/* Variables and functions */
 int /*<<< orphan*/  __remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void userfaultfd_event_complete(struct userfaultfd_ctx *ctx,
				       struct userfaultfd_wait_queue *ewq)
{
	ewq->msg.event = 0;
	wake_up_locked(&ctx->event_wqh);
	__remove_wait_queue(&ctx->event_wqh, &ewq->wq);
}
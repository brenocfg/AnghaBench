#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct request_context {int killed; int /*<<< orphan*/  refcount; TYPE_2__* outurb; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_1__* dev; int /*<<< orphan*/  transfer_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 int /*<<< orphan*/  EZUSB_CTX_REQ_TIMEOUT ; 
 int /*<<< orphan*/  EZUSB_CTX_RESP_TIMEOUT ; 
 int /*<<< orphan*/  URB_ASYNC_UNLINK ; 
 struct request_context* ctx ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ezusb_ctx_complete (struct request_context*) ; 
 int /*<<< orphan*/  ezusb_request_context_put (struct request_context*) ; 
 struct request_context* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  usb_unlink_urb (TYPE_2__*) ; 

__attribute__((used)) static void ezusb_request_timerfn(struct timer_list *t)
{
	struct request_context *ctx = from_timer(ctx, t, timer);

	ctx->outurb->transfer_flags |= URB_ASYNC_UNLINK;
	if (usb_unlink_urb(ctx->outurb) == -EINPROGRESS) {
		ctx->state = EZUSB_CTX_REQ_TIMEOUT;
	} else {
		ctx->state = EZUSB_CTX_RESP_TIMEOUT;
		dev_dbg(&ctx->outurb->dev->dev, "couldn't unlink\n");
		refcount_inc(&ctx->refcount);
		ctx->killed = 1;
		ezusb_ctx_complete(ctx);
		ezusb_request_context_put(ctx);
	}
}
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
struct request_context {int /*<<< orphan*/  state; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; TYPE_1__* upriv; } ;
struct ezusb_priv {int /*<<< orphan*/  req_lock; int /*<<< orphan*/  req_pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EZUSB_CTX_QUEUED ; 
 int /*<<< orphan*/  ezusb_req_queue_run (struct ezusb_priv*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ezusb_req_enqueue_run(struct ezusb_priv *upriv,
				  struct request_context *ctx)
{
	unsigned long flags;

	spin_lock_irqsave(&upriv->req_lock, flags);

	if (!ctx->upriv->udev) {
		spin_unlock_irqrestore(&upriv->req_lock, flags);
		goto done;
	}
	refcount_inc(&ctx->refcount);
	list_add_tail(&ctx->list, &upriv->req_pending);
	spin_unlock_irqrestore(&upriv->req_lock, flags);

	ctx->state = EZUSB_CTX_QUEUED;
	ezusb_req_queue_run(upriv);

 done:
	return;
}
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
typedef  void* u16 ;
struct request_context {int /*<<< orphan*/  timer; int /*<<< orphan*/  done; int /*<<< orphan*/  refcount; void* in_rid; void* out_rid; int /*<<< orphan*/  state; struct ezusb_priv* upriv; struct request_context* buf; int /*<<< orphan*/  outurb; } ;
struct ezusb_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULK_BUF_SIZE ; 
 int /*<<< orphan*/  EZUSB_CTX_START ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ezusb_request_timerfn ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct request_context*) ; 
 struct request_context* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct request_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request_context *ezusb_alloc_ctx(struct ezusb_priv *upriv,
					       u16 out_rid, u16 in_rid)
{
	struct request_context *ctx;

	ctx = kzalloc(sizeof(*ctx), GFP_ATOMIC);
	if (!ctx)
		return NULL;

	ctx->buf = kmalloc(BULK_BUF_SIZE, GFP_ATOMIC);
	if (!ctx->buf) {
		kfree(ctx);
		return NULL;
	}
	ctx->outurb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!ctx->outurb) {
		kfree(ctx->buf);
		kfree(ctx);
		return NULL;
	}

	ctx->upriv = upriv;
	ctx->state = EZUSB_CTX_START;
	ctx->out_rid = out_rid;
	ctx->in_rid = in_rid;

	refcount_set(&ctx->refcount, 1);
	init_completion(&ctx->done);

	timer_setup(&ctx->timer, ezusb_request_timerfn, 0);
	return ctx;
}
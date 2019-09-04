#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_userfaultfd_ctx {struct userfaultfd_ctx* ctx; } ;
struct TYPE_4__ {unsigned long from; unsigned long to; unsigned long len; } ;
struct TYPE_5__ {TYPE_1__ remap; } ;
struct TYPE_6__ {TYPE_2__ arg; int /*<<< orphan*/  event; } ;
struct userfaultfd_wait_queue {TYPE_3__ msg; } ;
struct userfaultfd_ctx {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  UFFD_EVENT_REMAP ; 
 int /*<<< orphan*/  msg_init (TYPE_3__*) ; 
 int /*<<< orphan*/  userfaultfd_ctx_put (struct userfaultfd_ctx*) ; 
 int /*<<< orphan*/  userfaultfd_event_wait_completion (struct userfaultfd_ctx*,struct userfaultfd_wait_queue*) ; 

void mremap_userfaultfd_complete(struct vm_userfaultfd_ctx *vm_ctx,
				 unsigned long from, unsigned long to,
				 unsigned long len)
{
	struct userfaultfd_ctx *ctx = vm_ctx->ctx;
	struct userfaultfd_wait_queue ewq;

	if (!ctx)
		return;

	if (to & ~PAGE_MASK) {
		userfaultfd_ctx_put(ctx);
		return;
	}

	msg_init(&ewq.msg);

	ewq.msg.event = UFFD_EVENT_REMAP;
	ewq.msg.arg.remap.from = from;
	ewq.msg.arg.remap.to = to;
	ewq.msg.arg.remap.len = len;

	userfaultfd_event_wait_completion(ctx, &ewq);
}
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
struct timerfd_ctx {int /*<<< orphan*/  cancel_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __timerfd_remove_cancel (struct timerfd_ctx*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timerfd_remove_cancel(struct timerfd_ctx *ctx)
{
	spin_lock(&ctx->cancel_lock);
	__timerfd_remove_cancel(ctx);
	spin_unlock(&ctx->cancel_lock);
}
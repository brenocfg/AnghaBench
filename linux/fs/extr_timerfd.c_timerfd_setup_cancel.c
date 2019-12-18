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
struct timerfd_ctx {scalar_t__ clockid; int might_cancel; int /*<<< orphan*/  cancel_lock; int /*<<< orphan*/  clist; } ;

/* Variables and functions */
 scalar_t__ CLOCK_REALTIME ; 
 scalar_t__ CLOCK_REALTIME_ALARM ; 
 int TFD_TIMER_ABSTIME ; 
 int TFD_TIMER_CANCEL_ON_SET ; 
 int /*<<< orphan*/  __timerfd_remove_cancel (struct timerfd_ctx*) ; 
 int /*<<< orphan*/  cancel_list ; 
 int /*<<< orphan*/  cancel_lock ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void timerfd_setup_cancel(struct timerfd_ctx *ctx, int flags)
{
	spin_lock(&ctx->cancel_lock);
	if ((ctx->clockid == CLOCK_REALTIME ||
	     ctx->clockid == CLOCK_REALTIME_ALARM) &&
	    (flags & TFD_TIMER_ABSTIME) && (flags & TFD_TIMER_CANCEL_ON_SET)) {
		if (!ctx->might_cancel) {
			ctx->might_cancel = true;
			spin_lock(&cancel_lock);
			list_add_rcu(&ctx->clist, &cancel_list);
			spin_unlock(&cancel_lock);
		}
	} else {
		__timerfd_remove_cancel(ctx);
	}
	spin_unlock(&ctx->cancel_lock);
}
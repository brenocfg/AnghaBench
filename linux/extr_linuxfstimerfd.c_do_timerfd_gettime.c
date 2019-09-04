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
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  tmr; int /*<<< orphan*/  alarm; } ;
struct timerfd_ctx {TYPE_3__ wqh; scalar_t__ tintv; TYPE_2__ t; int /*<<< orphan*/  ticks; scalar_t__ expired; } ;
struct itimerspec64 {void* it_interval; void* it_value; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_4__ {struct timerfd_ctx* private_data; } ;

/* Variables and functions */
 int alarm_forward_now (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  alarm_restart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int hrtimer_forward_now (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  hrtimer_restart (int /*<<< orphan*/ *) ; 
 scalar_t__ isalarm (struct timerfd_ctx*) ; 
 void* ktime_to_timespec64 (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int timerfd_fget (int,struct fd*) ; 
 scalar_t__ timerfd_get_remaining (struct timerfd_ctx*) ; 

__attribute__((used)) static int do_timerfd_gettime(int ufd, struct itimerspec64 *t)
{
	struct fd f;
	struct timerfd_ctx *ctx;
	int ret = timerfd_fget(ufd, &f);
	if (ret)
		return ret;
	ctx = f.file->private_data;

	spin_lock_irq(&ctx->wqh.lock);
	if (ctx->expired && ctx->tintv) {
		ctx->expired = 0;

		if (isalarm(ctx)) {
			ctx->ticks +=
				alarm_forward_now(
					&ctx->t.alarm, ctx->tintv) - 1;
			alarm_restart(&ctx->t.alarm);
		} else {
			ctx->ticks +=
				hrtimer_forward_now(&ctx->t.tmr, ctx->tintv)
				- 1;
			hrtimer_restart(&ctx->t.tmr);
		}
	}
	t->it_value = ktime_to_timespec64(timerfd_get_remaining(ctx));
	t->it_interval = ktime_to_timespec64(ctx->tintv);
	spin_unlock_irq(&ctx->wqh.lock);
	fdput(f);
	return 0;
}
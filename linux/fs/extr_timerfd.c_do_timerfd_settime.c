#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_9__ {int /*<<< orphan*/  timer; } ;
struct TYPE_7__ {int /*<<< orphan*/  tmr; TYPE_4__ alarm; } ;
struct timerfd_ctx {TYPE_3__ wqh; scalar_t__ tintv; TYPE_2__ t; scalar_t__ expired; } ;
struct itimerspec64 {void* it_interval; void* it_value; } ;
struct fd {TYPE_1__* file; } ;
struct TYPE_6__ {struct timerfd_ctx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_WAKE_ALARM ; 
 int EINVAL ; 
 int EPERM ; 
 int TFD_SETTIME_FLAGS ; 
 int /*<<< orphan*/  alarm_forward_now (TYPE_4__*,scalar_t__) ; 
 scalar_t__ alarm_try_to_cancel (TYPE_4__*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  hrtimer_cancel_wait_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_forward_now (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hrtimer_try_to_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ isalarm (struct timerfd_ctx*) ; 
 int /*<<< orphan*/  itimerspec64_valid (struct itimerspec64 const*) ; 
 void* ktime_to_timespec64 (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int timerfd_fget (int,struct fd*) ; 
 scalar_t__ timerfd_get_remaining (struct timerfd_ctx*) ; 
 int timerfd_setup (struct timerfd_ctx*,int,struct itimerspec64 const*) ; 
 int /*<<< orphan*/  timerfd_setup_cancel (struct timerfd_ctx*,int) ; 

__attribute__((used)) static int do_timerfd_settime(int ufd, int flags, 
		const struct itimerspec64 *new,
		struct itimerspec64 *old)
{
	struct fd f;
	struct timerfd_ctx *ctx;
	int ret;

	if ((flags & ~TFD_SETTIME_FLAGS) ||
		 !itimerspec64_valid(new))
		return -EINVAL;

	ret = timerfd_fget(ufd, &f);
	if (ret)
		return ret;
	ctx = f.file->private_data;

	if (isalarm(ctx) && !capable(CAP_WAKE_ALARM)) {
		fdput(f);
		return -EPERM;
	}

	timerfd_setup_cancel(ctx, flags);

	/*
	 * We need to stop the existing timer before reprogramming
	 * it to the new values.
	 */
	for (;;) {
		spin_lock_irq(&ctx->wqh.lock);

		if (isalarm(ctx)) {
			if (alarm_try_to_cancel(&ctx->t.alarm) >= 0)
				break;
		} else {
			if (hrtimer_try_to_cancel(&ctx->t.tmr) >= 0)
				break;
		}
		spin_unlock_irq(&ctx->wqh.lock);

		if (isalarm(ctx))
			hrtimer_cancel_wait_running(&ctx->t.alarm.timer);
		else
			hrtimer_cancel_wait_running(&ctx->t.tmr);
	}

	/*
	 * If the timer is expired and it's periodic, we need to advance it
	 * because the caller may want to know the previous expiration time.
	 * We do not update "ticks" and "expired" since the timer will be
	 * re-programmed again in the following timerfd_setup() call.
	 */
	if (ctx->expired && ctx->tintv) {
		if (isalarm(ctx))
			alarm_forward_now(&ctx->t.alarm, ctx->tintv);
		else
			hrtimer_forward_now(&ctx->t.tmr, ctx->tintv);
	}

	old->it_value = ktime_to_timespec64(timerfd_get_remaining(ctx));
	old->it_interval = ktime_to_timespec64(ctx->tintv);

	/*
	 * Re-program the timer to the new value ...
	 */
	ret = timerfd_setup(ctx, flags, new);

	spin_unlock_irq(&ctx->wqh.lock);
	fdput(f);
	return ret;
}
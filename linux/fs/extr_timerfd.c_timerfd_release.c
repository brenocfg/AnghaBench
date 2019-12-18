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
struct TYPE_2__ {int /*<<< orphan*/  tmr; int /*<<< orphan*/  alarm; } ;
struct timerfd_ctx {TYPE_1__ t; } ;
struct inode {int dummy; } ;
struct file {struct timerfd_ctx* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  alarm_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ isalarm (struct timerfd_ctx*) ; 
 int /*<<< orphan*/  kfree_rcu (struct timerfd_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  timerfd_remove_cancel (struct timerfd_ctx*) ; 

__attribute__((used)) static int timerfd_release(struct inode *inode, struct file *file)
{
	struct timerfd_ctx *ctx = file->private_data;

	timerfd_remove_cancel(ctx);

	if (isalarm(ctx))
		alarm_cancel(&ctx->t.alarm);
	else
		hrtimer_cancel(&ctx->t.tmr);
	kfree_rcu(ctx, rcu);
	return 0;
}
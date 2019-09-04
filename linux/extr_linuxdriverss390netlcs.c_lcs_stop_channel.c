#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lcs_channel {scalar_t__ state; int /*<<< orphan*/  wait_q; TYPE_1__* ccwdev; } ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LCS_CH_STATE_HALTED ; 
 scalar_t__ LCS_CH_STATE_INIT ; 
 scalar_t__ LCS_CH_STATE_STOPPED ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ccw_device_halt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  lcs_clear_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lcs_stop_channel(struct lcs_channel *channel)
{
	unsigned long flags;
	int rc;

	if (channel->state == LCS_CH_STATE_STOPPED)
		return 0;
	LCS_DBF_TEXT(4,trace,"haltsch");
	LCS_DBF_TEXT_(4, trace, "%s", dev_name(&channel->ccwdev->dev));
	channel->state = LCS_CH_STATE_INIT;
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_halt(channel->ccwdev, (addr_t) channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	if (rc) {
		LCS_DBF_TEXT_(4, trace, "ehsc%s",
			      dev_name(&channel->ccwdev->dev));
		return rc;
	}
	/* Asynchronous halt initialted. Wait for its completion. */
	wait_event(channel->wait_q, (channel->state == LCS_CH_STATE_HALTED));
	lcs_clear_channel(channel);
	return 0;
}
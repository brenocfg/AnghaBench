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
struct TYPE_2__ {int ctrl_response_valid; } ;
struct htc_target {int /*<<< orphan*/  rx_lock; TYPE_1__ pipe; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HTC_TARGET_RESPONSE_POLL_COUNT ; 
 int /*<<< orphan*/  HTC_TARGET_RESPONSE_POLL_WAIT ; 
 int /*<<< orphan*/  ath6kl_warn (char*) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int htc_wait_recv_ctrl_message(struct htc_target *target)
{
	int count = HTC_TARGET_RESPONSE_POLL_COUNT;

	while (count > 0) {
		spin_lock_bh(&target->rx_lock);

		if (target->pipe.ctrl_response_valid) {
			target->pipe.ctrl_response_valid = false;
			spin_unlock_bh(&target->rx_lock);
			break;
		}

		spin_unlock_bh(&target->rx_lock);

		count--;

		msleep_interruptible(HTC_TARGET_RESPONSE_POLL_WAIT);
	}

	if (count <= 0) {
		ath6kl_warn("htc pipe control receive timeout!\n");
		return -ETIMEDOUT;
	}

	return 0;
}
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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ams_delta_lock ; 
 int ams_delta_muted ; 
 scalar_t__ cx81801_cmd_pending ; 
 int /*<<< orphan*/  gpiod_modem_codec ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx81801_timeout(struct timer_list *unused)
{
	int muted;

	spin_lock(&ams_delta_lock);
	cx81801_cmd_pending = 0;
	muted = ams_delta_muted;
	spin_unlock(&ams_delta_lock);

	/* Reconnect the codec DAI back from the modem to the CPU DAI
	 * only if digital mute still off */
	if (!muted)
		gpiod_set_value(gpiod_modem_codec, 0);
}
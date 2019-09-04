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
struct link {int /*<<< orphan*/  work; } ;
struct rt2x00_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  intf_sta_count; int /*<<< orphan*/  intf_ap_count; struct link link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_PRESENT ; 
 int /*<<< orphan*/  DEVICE_STATE_SCANNING ; 
 int /*<<< orphan*/  LINK_TUNE_INTERVAL ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00link_reset_tuner (struct rt2x00_dev*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rt2x00link_start_tuner(struct rt2x00_dev *rt2x00dev)
{
	struct link *link = &rt2x00dev->link;

	/*
	 * Single monitor mode interfaces should never have
	 * work with link tuners.
	 */
	if (!rt2x00dev->intf_ap_count && !rt2x00dev->intf_sta_count)
		return;

	/*
	 * While scanning, link tuning is disabled. By default
	 * the most sensitive settings will be used to make sure
	 * that all beacons and probe responses will be received
	 * during the scan.
	 */
	if (test_bit(DEVICE_STATE_SCANNING, &rt2x00dev->flags))
		return;

	rt2x00link_reset_tuner(rt2x00dev, false);

	if (test_bit(DEVICE_STATE_PRESENT, &rt2x00dev->flags))
		ieee80211_queue_delayed_work(rt2x00dev->hw,
					     &link->work, LINK_TUNE_INTERVAL);
}
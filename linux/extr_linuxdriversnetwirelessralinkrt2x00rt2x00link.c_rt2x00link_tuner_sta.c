#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dot11FCSErrorCount; } ;
struct link_qual {int /*<<< orphan*/  rssi; int /*<<< orphan*/  rx_success; scalar_t__ rx_failed; } ;
struct TYPE_8__ {struct link_qual qual; } ;
struct rt2x00_dev {TYPE_3__* ops; TYPE_1__ low_level_stats; TYPE_4__ link; } ;
struct link {int /*<<< orphan*/  count; int /*<<< orphan*/  avg_rssi; } ;
struct TYPE_7__ {TYPE_2__* lib; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* link_tuner ) (struct rt2x00_dev*,struct link_qual*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* link_stats ) (struct rt2x00_dev*,struct link_qual*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_RSSI ; 
 scalar_t__ rt2x00_has_cap_link_tuning (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00leds_led_quality (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ rt2x00lib_antenna_diversity (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00link_get_avg_rssi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00link_reset_qual (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  stub1 (struct rt2x00_dev*,struct link_qual*) ; 
 int /*<<< orphan*/  stub2 (struct rt2x00_dev*,struct link_qual*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2x00link_tuner_sta(struct rt2x00_dev *rt2x00dev, struct link *link)
{
	struct link_qual *qual = &rt2x00dev->link.qual;

	/*
	 * Update statistics.
	 */
	rt2x00dev->ops->lib->link_stats(rt2x00dev, qual);
	rt2x00dev->low_level_stats.dot11FCSErrorCount += qual->rx_failed;

	/*
	 * Update quality RSSI for link tuning,
	 * when we have received some frames and we managed to
	 * collect the RSSI data we could use this. Otherwise we
	 * must fallback to the default RSSI value.
	 */
	if (!qual->rx_success)
		qual->rssi = DEFAULT_RSSI;
	else
		qual->rssi = rt2x00link_get_avg_rssi(&link->avg_rssi);

	/*
	 * Check if link tuning is supported by the hardware, some hardware
	 * do not support link tuning at all, while other devices can disable
	 * the feature from the EEPROM.
	 */
	if (rt2x00_has_cap_link_tuning(rt2x00dev))
		rt2x00dev->ops->lib->link_tuner(rt2x00dev, qual, link->count);

	/*
	 * Send a signal to the led to update the led signal strength.
	 */
	rt2x00leds_led_quality(rt2x00dev, qual->rssi);

	/*
	 * Evaluate antenna setup, make this the last step when
	 * rt2x00lib_antenna_diversity made changes the quality
	 * statistics will be reset.
	 */
	if (rt2x00lib_antenna_diversity(rt2x00dev))
		rt2x00link_reset_qual(rt2x00dev);
}
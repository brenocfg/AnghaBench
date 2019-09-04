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
struct tpt_led_trigger {unsigned long tx_bytes; unsigned long rx_bytes; unsigned long prev_traffic; } ;
struct ieee80211_local {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 

__attribute__((used)) static unsigned long tpt_trig_traffic(struct ieee80211_local *local,
				      struct tpt_led_trigger *tpt_trig)
{
	unsigned long traffic, delta;

	traffic = tpt_trig->tx_bytes + tpt_trig->rx_bytes;

	delta = traffic - tpt_trig->prev_traffic;
	tpt_trig->prev_traffic = traffic;
	return DIV_ROUND_UP(delta, 1024 / 8);
}
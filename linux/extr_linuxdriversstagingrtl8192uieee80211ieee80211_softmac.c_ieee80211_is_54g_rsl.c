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
struct ieee80211_network {scalar_t__ rates_ex_len; int rates_len; } ;

/* Variables and functions */

short ieee80211_is_54g(const struct ieee80211_network *net)
{
	return (net->rates_ex_len > 0) || (net->rates_len > 4);
}
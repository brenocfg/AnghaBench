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
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
#define  NL80211_REGDOM_SET_BY_CORE 131 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 130 
#define  NL80211_REGDOM_SET_BY_DRIVER 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int /*<<< orphan*/  WARN_ON (int) ; 

const char *reg_initiator_name(enum nl80211_reg_initiator initiator)
{
	switch (initiator) {
	case NL80211_REGDOM_SET_BY_CORE:
		return "core";
	case NL80211_REGDOM_SET_BY_USER:
		return "user";
	case NL80211_REGDOM_SET_BY_DRIVER:
		return "driver";
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		return "country element";
	default:
		WARN_ON(1);
		return "bug";
	}
}
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
typedef  int /*<<< orphan*/  u8 ;
struct rtl8xxxu_priv {int dummy; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_LINKTYPE_ADHOC ; 
 int /*<<< orphan*/  MSR_LINKTYPE_AP ; 
 int /*<<< orphan*/  MSR_LINKTYPE_MASK ; 
 int /*<<< orphan*/  MSR_LINKTYPE_NONE ; 
 int /*<<< orphan*/  MSR_LINKTYPE_STATION ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_STATION 129 
#define  NL80211_IFTYPE_UNSPECIFIED 128 
 int /*<<< orphan*/  REG_MSR ; 
 int /*<<< orphan*/  rtl8xxxu_read8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl8xxxu_set_linktype(struct rtl8xxxu_priv *priv,
				  enum nl80211_iftype linktype)
{
	u8 val8;

	val8 = rtl8xxxu_read8(priv, REG_MSR);
	val8 &= ~MSR_LINKTYPE_MASK;

	switch (linktype) {
	case NL80211_IFTYPE_UNSPECIFIED:
		val8 |= MSR_LINKTYPE_NONE;
		break;
	case NL80211_IFTYPE_ADHOC:
		val8 |= MSR_LINKTYPE_ADHOC;
		break;
	case NL80211_IFTYPE_STATION:
		val8 |= MSR_LINKTYPE_STATION;
		break;
	case NL80211_IFTYPE_AP:
		val8 |= MSR_LINKTYPE_AP;
		break;
	default:
		goto out;
	}

	rtl8xxxu_write8(priv, REG_MSR, val8);
out:
	return;
}
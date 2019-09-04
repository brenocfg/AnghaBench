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
struct rtw_regulatory {int dummy; } ;
struct ieee80211_regdomain {int dummy; } ;

/* Variables and functions */
 struct ieee80211_regdomain const rtw_regdom_rd ; 

__attribute__((used)) static const struct ieee80211_regdomain *_rtw_regdomain_select(struct
							       rtw_regulatory
							       *reg)
{
	return &rtw_regdom_rd;
}
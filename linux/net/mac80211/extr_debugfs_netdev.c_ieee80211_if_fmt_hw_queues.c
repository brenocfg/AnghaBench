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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  cab_queue; int /*<<< orphan*/ * hw_queue; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;
typedef  int ssize_t ;

/* Variables and functions */
 size_t IEEE80211_AC_BE ; 
 size_t IEEE80211_AC_BK ; 
 size_t IEEE80211_AC_VI ; 
 size_t IEEE80211_AC_VO ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int scnprintf (char*,int,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static ssize_t
ieee80211_if_fmt_hw_queues(const struct ieee80211_sub_if_data *sdata,
			   char *buf, int buflen)
{
	int len;

	len = scnprintf(buf, buflen, "AC queues: VO:%d VI:%d BE:%d BK:%d\n",
			sdata->vif.hw_queue[IEEE80211_AC_VO],
			sdata->vif.hw_queue[IEEE80211_AC_VI],
			sdata->vif.hw_queue[IEEE80211_AC_BE],
			sdata->vif.hw_queue[IEEE80211_AC_BK]);

	if (sdata->vif.type == NL80211_IFTYPE_AP)
		len += scnprintf(buf + len, buflen - len, "cab queue: %d\n",
				 sdata->vif.cab_queue);

	return len;
}
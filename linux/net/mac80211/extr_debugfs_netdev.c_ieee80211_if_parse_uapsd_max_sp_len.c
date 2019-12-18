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
struct ieee80211_if_managed {unsigned long uapsd_max_sp_len; } ;
struct TYPE_2__ {struct ieee80211_if_managed mgd; } ;
struct ieee80211_sub_if_data {TYPE_1__ u; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 unsigned long IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static ssize_t ieee80211_if_parse_uapsd_max_sp_len(
	struct ieee80211_sub_if_data *sdata, const char *buf, int buflen)
{
	struct ieee80211_if_managed *ifmgd = &sdata->u.mgd;
	unsigned long val;
	int ret;

	ret = kstrtoul(buf, 0, &val);
	if (ret)
		return -EINVAL;

	if (val & ~IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK)
		return -ERANGE;

	ifmgd->uapsd_max_sp_len = val;

	return buflen;
}
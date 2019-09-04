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
typedef  scalar_t__ u64 ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ drv_get_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,unsigned long long) ; 

__attribute__((used)) static ssize_t ieee80211_if_fmt_tsf(
	const struct ieee80211_sub_if_data *sdata, char *buf, int buflen)
{
	struct ieee80211_local *local = sdata->local;
	u64 tsf;

	tsf = drv_get_tsf(local, (struct ieee80211_sub_if_data *)sdata);

	return scnprintf(buf, buflen, "0x%016llx\n", (unsigned long long) tsf);
}
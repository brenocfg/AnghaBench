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
struct ieee80211_sub_if_data {int flags; int /*<<< orphan*/  name; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IEEE80211_SDATA_IN_DRIVER ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool check_sdata_in_driver(struct ieee80211_sub_if_data *sdata)
{
	return !WARN(!(sdata->flags & IEEE80211_SDATA_IN_DRIVER),
		     "%s:  Failed check-sdata-in-driver check, flags: 0x%x\n",
		     sdata->dev ? sdata->dev->name : sdata->name, sdata->flags);
}
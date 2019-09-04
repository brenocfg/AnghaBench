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
struct wireless_dev {int /*<<< orphan*/  wiphy; } ;
struct brcmf_cfg80211_info {int dummy; } ;

/* Variables and functions */
 struct brcmf_cfg80211_info* wiphy_to_cfg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct brcmf_cfg80211_info *wdev_to_cfg(struct wireless_dev *wd)
{
	return wiphy_to_cfg(wd->wiphy);
}
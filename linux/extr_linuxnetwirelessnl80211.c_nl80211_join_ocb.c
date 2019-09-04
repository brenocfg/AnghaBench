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
struct sk_buff {int dummy; } ;
struct ocb_setup {int /*<<< orphan*/  chandef; } ;
struct net_device {int dummy; } ;
struct genl_info {struct net_device** user_ptr; } ;
typedef  struct net_device cfg80211_registered_device ;

/* Variables and functions */
 int cfg80211_join_ocb (struct net_device*,struct net_device*,struct ocb_setup*) ; 
 int nl80211_parse_chandef (struct net_device*,struct genl_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nl80211_join_ocb(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct ocb_setup setup = {};
	int err;

	err = nl80211_parse_chandef(rdev, info, &setup.chandef);
	if (err)
		return err;

	return cfg80211_join_ocb(rdev, dev, &setup);
}
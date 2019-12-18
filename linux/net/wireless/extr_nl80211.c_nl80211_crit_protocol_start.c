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
typedef  scalar_t__ u16 ;
struct wireless_dev {scalar_t__ crit_proto_nlportid; TYPE_1__* ops; } ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__ snd_portid; scalar_t__* attrs; struct wireless_dev** user_ptr; } ;
struct cfg80211_registered_device {scalar_t__ crit_proto_nlportid; TYPE_1__* ops; } ;
typedef  enum nl80211_crit_proto_id { ____Placeholder_nl80211_crit_proto_id } nl80211_crit_proto_id ;
struct TYPE_2__ {int /*<<< orphan*/  crit_proto_stop; int /*<<< orphan*/  crit_proto_start; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ERANGE ; 
 size_t NL80211_ATTR_CRIT_PROT_ID ; 
 size_t NL80211_ATTR_MAX_CRIT_PROT_DURATION ; 
 scalar_t__ NL80211_CRIT_PROTO_MAX_DURATION ; 
 int NL80211_CRIT_PROTO_UNSPEC ; 
 int NUM_NL80211_CRIT_PROTO ; 
 scalar_t__ WARN_ON (int) ; 
 void* nla_get_u16 (scalar_t__) ; 
 int rdev_crit_proto_start (struct wireless_dev*,struct wireless_dev*,int,scalar_t__) ; 

__attribute__((used)) static int nl80211_crit_protocol_start(struct sk_buff *skb,
				       struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct wireless_dev *wdev = info->user_ptr[1];
	enum nl80211_crit_proto_id proto = NL80211_CRIT_PROTO_UNSPEC;
	u16 duration;
	int ret;

	if (!rdev->ops->crit_proto_start)
		return -EOPNOTSUPP;

	if (WARN_ON(!rdev->ops->crit_proto_stop))
		return -EINVAL;

	if (rdev->crit_proto_nlportid)
		return -EBUSY;

	/* determine protocol if provided */
	if (info->attrs[NL80211_ATTR_CRIT_PROT_ID])
		proto = nla_get_u16(info->attrs[NL80211_ATTR_CRIT_PROT_ID]);

	if (proto >= NUM_NL80211_CRIT_PROTO)
		return -EINVAL;

	/* timeout must be provided */
	if (!info->attrs[NL80211_ATTR_MAX_CRIT_PROT_DURATION])
		return -EINVAL;

	duration =
		nla_get_u16(info->attrs[NL80211_ATTR_MAX_CRIT_PROT_DURATION]);

	if (duration > NL80211_CRIT_PROTO_MAX_DURATION)
		return -ERANGE;

	ret = rdev_crit_proto_start(rdev, wdev, proto, duration);
	if (!ret)
		rdev->crit_proto_nlportid = info->snd_portid;

	return ret;
}
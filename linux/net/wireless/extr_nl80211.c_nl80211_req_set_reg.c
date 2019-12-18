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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; int /*<<< orphan*/  snd_portid; } ;
typedef  enum nl80211_user_reg_hint_type { ____Placeholder_nl80211_user_reg_hint_type } nl80211_user_reg_hint_type ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 size_t NL80211_ATTR_REG_ALPHA2 ; 
 size_t NL80211_ATTR_REG_INDOOR ; 
 size_t NL80211_ATTR_SOCKET_OWNER ; 
 size_t NL80211_ATTR_USER_REG_HINT_TYPE ; 
#define  NL80211_USER_REG_HINT_CELL_BASE 130 
#define  NL80211_USER_REG_HINT_INDOOR 129 
#define  NL80211_USER_REG_HINT_USER 128 
 int /*<<< orphan*/  cfg80211_regdomain ; 
 char* nla_data (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int regulatory_hint_indoor (int,int /*<<< orphan*/ ) ; 
 int regulatory_hint_user (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nl80211_req_set_reg(struct sk_buff *skb, struct genl_info *info)
{
	char *data = NULL;
	bool is_indoor;
	enum nl80211_user_reg_hint_type user_reg_hint_type;
	u32 owner_nlportid;

	/*
	 * You should only get this when cfg80211 hasn't yet initialized
	 * completely when built-in to the kernel right between the time
	 * window between nl80211_init() and regulatory_init(), if that is
	 * even possible.
	 */
	if (unlikely(!rcu_access_pointer(cfg80211_regdomain)))
		return -EINPROGRESS;

	if (info->attrs[NL80211_ATTR_USER_REG_HINT_TYPE])
		user_reg_hint_type =
		  nla_get_u32(info->attrs[NL80211_ATTR_USER_REG_HINT_TYPE]);
	else
		user_reg_hint_type = NL80211_USER_REG_HINT_USER;

	switch (user_reg_hint_type) {
	case NL80211_USER_REG_HINT_USER:
	case NL80211_USER_REG_HINT_CELL_BASE:
		if (!info->attrs[NL80211_ATTR_REG_ALPHA2])
			return -EINVAL;

		data = nla_data(info->attrs[NL80211_ATTR_REG_ALPHA2]);
		return regulatory_hint_user(data, user_reg_hint_type);
	case NL80211_USER_REG_HINT_INDOOR:
		if (info->attrs[NL80211_ATTR_SOCKET_OWNER]) {
			owner_nlportid = info->snd_portid;
			is_indoor = !!info->attrs[NL80211_ATTR_REG_INDOOR];
		} else {
			owner_nlportid = 0;
			is_indoor = true;
		}

		return regulatory_hint_indoor(is_indoor, owner_nlportid);
	default:
		return -EINVAL;
	}
}
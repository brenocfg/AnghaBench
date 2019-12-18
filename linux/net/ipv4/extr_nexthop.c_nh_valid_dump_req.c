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
typedef  int u32 ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nhmsg {scalar_t__ nh_flags; scalar_t__ nh_scope; scalar_t__ resvd; scalar_t__ nh_protocol; } ;
struct netlink_ext_ack {int dummy; } ;
struct netlink_callback {struct netlink_ext_ack* extack; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
#define  NHA_GROUPS 130 
#define  NHA_MASTER 129 
 int NHA_MAX ; 
#define  NHA_OIF 128 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 struct nhmsg* nlmsg_data (struct nlmsghdr const*) ; 
 int nlmsg_parse (struct nlmsghdr const*,int,struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtm_nh_policy ; 

__attribute__((used)) static int nh_valid_dump_req(const struct nlmsghdr *nlh, int *dev_idx,
			     int *master_idx, bool *group_filter,
			     struct netlink_callback *cb)
{
	struct netlink_ext_ack *extack = cb->extack;
	struct nlattr *tb[NHA_MAX + 1];
	struct nhmsg *nhm;
	int err, i;
	u32 idx;

	err = nlmsg_parse(nlh, sizeof(*nhm), tb, NHA_MAX, rtm_nh_policy,
			  NULL);
	if (err < 0)
		return err;

	for (i = 0; i <= NHA_MAX; ++i) {
		if (!tb[i])
			continue;

		switch (i) {
		case NHA_OIF:
			idx = nla_get_u32(tb[i]);
			if (idx > INT_MAX) {
				NL_SET_ERR_MSG(extack, "Invalid device index");
				return -EINVAL;
			}
			*dev_idx = idx;
			break;
		case NHA_MASTER:
			idx = nla_get_u32(tb[i]);
			if (idx > INT_MAX) {
				NL_SET_ERR_MSG(extack, "Invalid master device index");
				return -EINVAL;
			}
			*master_idx = idx;
			break;
		case NHA_GROUPS:
			*group_filter = true;
			break;
		default:
			NL_SET_ERR_MSG(extack, "Unsupported attribute in dump request");
			return -EINVAL;
		}
	}

	nhm = nlmsg_data(nlh);
	if (nhm->nh_protocol || nhm->resvd || nhm->nh_scope || nhm->nh_flags) {
		NL_SET_ERR_MSG(extack, "Invalid values in header for nexthop dump request");
		return -EINVAL;
	}

	return 0;
}
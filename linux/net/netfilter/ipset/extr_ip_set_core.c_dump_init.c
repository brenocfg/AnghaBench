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
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct nlattr {int dummy; } ;
struct nfgenmsg {int dummy; } ;
struct netlink_callback {unsigned long* args; int /*<<< orphan*/  skb; } ;
struct ip_set_net {int dummy; } ;
struct ip_set {int dummy; } ;
typedef  unsigned long ip_set_id_t ;

/* Variables and functions */
 int DUMP_ALL ; 
 int DUMP_ONE ; 
 int ENOENT ; 
 int /*<<< orphan*/  IPSET_ATTR_CMD_MAX ; 
 size_t IPSET_ATTR_FLAGS ; 
 size_t IPSET_ATTR_PROTOCOL ; 
 size_t IPSET_ATTR_SETNAME ; 
 size_t IPSET_CB_DUMP ; 
 size_t IPSET_CB_INDEX ; 
 size_t IPSET_CB_NET ; 
 size_t IPSET_CB_PROTO ; 
 struct ip_set* find_set_and_id (struct ip_set_net*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  ip_set_dump_policy ; 
 int ip_set_get_h32 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 unsigned long nla_get_u8 (struct nlattr*) ; 
 int nla_parse (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nlmsghdr* nlmsg_hdr (int /*<<< orphan*/ ) ; 
 int nlmsg_total_size (int) ; 

__attribute__((used)) static int
dump_init(struct netlink_callback *cb, struct ip_set_net *inst)
{
	struct nlmsghdr *nlh = nlmsg_hdr(cb->skb);
	int min_len = nlmsg_total_size(sizeof(struct nfgenmsg));
	struct nlattr *cda[IPSET_ATTR_CMD_MAX + 1];
	struct nlattr *attr = (void *)nlh + min_len;
	u32 dump_type;
	ip_set_id_t index;
	int ret;

	ret = nla_parse(cda, IPSET_ATTR_CMD_MAX, attr,
			nlh->nlmsg_len - min_len,
			ip_set_dump_policy, NULL);
	if (ret)
		return ret;

	cb->args[IPSET_CB_PROTO] = nla_get_u8(cda[IPSET_ATTR_PROTOCOL]);
	if (cda[IPSET_ATTR_SETNAME]) {
		struct ip_set *set;

		set = find_set_and_id(inst, nla_data(cda[IPSET_ATTR_SETNAME]),
				      &index);
		if (!set)
			return -ENOENT;

		dump_type = DUMP_ONE;
		cb->args[IPSET_CB_INDEX] = index;
	} else {
		dump_type = DUMP_ALL;
	}

	if (cda[IPSET_ATTR_FLAGS]) {
		u32 f = ip_set_get_h32(cda[IPSET_ATTR_FLAGS]);

		dump_type |= (f << 16);
	}
	cb->args[IPSET_CB_NET] = (unsigned long)inst;
	cb->args[IPSET_CB_DUMP] = dump_type;

	return 0;
}
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
typedef  scalar_t__ uint32_t ;
struct sw_flow_key {int dummy; } ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; scalar_t__ data; } ;
struct ovs_header {int dp_ifindex; } ;
struct nlmsghdr {unsigned int nlmsg_len; } ;
struct nlattr {scalar_t__ nla_len; } ;
struct dp_upcall_info {int /*<<< orphan*/  portid; scalar_t__ mru; scalar_t__ actions_len; int /*<<< orphan*/  actions; int /*<<< orphan*/  egress_tun_info; scalar_t__ userdata; int /*<<< orphan*/  cmd; } ;
struct datapath {int user_features; } ;
struct TYPE_2__ {int /*<<< orphan*/  acts_origlen; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EFBIG ; 
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_1__* OVS_CB (struct sk_buff*) ; 
 int OVS_DP_F_UNALIGNED ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_ACTIONS ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_EGRESS_TUN_KEY ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_KEY ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_LEN ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_MRU ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_PACKET ; 
 int /*<<< orphan*/  OVS_PACKET_ATTR_USERDATA ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  __nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* __vlan_hwaccel_push_inside (struct sk_buff*) ; 
 int /*<<< orphan*/  dp_packet_genl_family ; 
 struct sk_buff* genlmsg_new (size_t,int /*<<< orphan*/ ) ; 
 struct ovs_header* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int get_dpifindex (struct datapath*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nla_attr_size (scalar_t__) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_len (scalar_t__) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,unsigned int) ; 
 struct nlattr* nla_reserve (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ovs_dp_get_net (struct datapath*) ; 
 int ovs_nla_put_actions (int /*<<< orphan*/ ,scalar_t__,struct sk_buff*) ; 
 int ovs_nla_put_key (struct sw_flow_key const*,struct sw_flow_key const*,int /*<<< orphan*/ ,int,struct sk_buff*) ; 
 int ovs_nla_put_tunnel_info (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad_packet (struct datapath*,struct sk_buff*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_csum_hwoffload_help (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tx_error (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int skb_zerocopy (struct sk_buff*,struct sk_buff*,scalar_t__,unsigned int) ; 
 unsigned int skb_zerocopy_headlen (struct sk_buff*) ; 
 size_t upcall_msg_size (struct dp_upcall_info const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int queue_userspace_packet(struct datapath *dp, struct sk_buff *skb,
				  const struct sw_flow_key *key,
				  const struct dp_upcall_info *upcall_info,
				  uint32_t cutlen)
{
	struct ovs_header *upcall;
	struct sk_buff *nskb = NULL;
	struct sk_buff *user_skb = NULL; /* to be queued to userspace */
	struct nlattr *nla;
	size_t len;
	unsigned int hlen;
	int err, dp_ifindex;

	dp_ifindex = get_dpifindex(dp);
	if (!dp_ifindex)
		return -ENODEV;

	if (skb_vlan_tag_present(skb)) {
		nskb = skb_clone(skb, GFP_ATOMIC);
		if (!nskb)
			return -ENOMEM;

		nskb = __vlan_hwaccel_push_inside(nskb);
		if (!nskb)
			return -ENOMEM;

		skb = nskb;
	}

	if (nla_attr_size(skb->len) > USHRT_MAX) {
		err = -EFBIG;
		goto out;
	}

	/* Complete checksum if needed */
	if (skb->ip_summed == CHECKSUM_PARTIAL &&
	    (err = skb_csum_hwoffload_help(skb, 0)))
		goto out;

	/* Older versions of OVS user space enforce alignment of the last
	 * Netlink attribute to NLA_ALIGNTO which would require extensive
	 * padding logic. Only perform zerocopy if padding is not required.
	 */
	if (dp->user_features & OVS_DP_F_UNALIGNED)
		hlen = skb_zerocopy_headlen(skb);
	else
		hlen = skb->len;

	len = upcall_msg_size(upcall_info, hlen - cutlen,
			      OVS_CB(skb)->acts_origlen);
	user_skb = genlmsg_new(len, GFP_ATOMIC);
	if (!user_skb) {
		err = -ENOMEM;
		goto out;
	}

	upcall = genlmsg_put(user_skb, 0, 0, &dp_packet_genl_family,
			     0, upcall_info->cmd);
	if (!upcall) {
		err = -EINVAL;
		goto out;
	}
	upcall->dp_ifindex = dp_ifindex;

	err = ovs_nla_put_key(key, key, OVS_PACKET_ATTR_KEY, false, user_skb);
	if (err)
		goto out;

	if (upcall_info->userdata)
		__nla_put(user_skb, OVS_PACKET_ATTR_USERDATA,
			  nla_len(upcall_info->userdata),
			  nla_data(upcall_info->userdata));

	if (upcall_info->egress_tun_info) {
		nla = nla_nest_start_noflag(user_skb,
					    OVS_PACKET_ATTR_EGRESS_TUN_KEY);
		if (!nla) {
			err = -EMSGSIZE;
			goto out;
		}
		err = ovs_nla_put_tunnel_info(user_skb,
					      upcall_info->egress_tun_info);
		if (err)
			goto out;

		nla_nest_end(user_skb, nla);
	}

	if (upcall_info->actions_len) {
		nla = nla_nest_start_noflag(user_skb, OVS_PACKET_ATTR_ACTIONS);
		if (!nla) {
			err = -EMSGSIZE;
			goto out;
		}
		err = ovs_nla_put_actions(upcall_info->actions,
					  upcall_info->actions_len,
					  user_skb);
		if (!err)
			nla_nest_end(user_skb, nla);
		else
			nla_nest_cancel(user_skb, nla);
	}

	/* Add OVS_PACKET_ATTR_MRU */
	if (upcall_info->mru) {
		if (nla_put_u16(user_skb, OVS_PACKET_ATTR_MRU,
				upcall_info->mru)) {
			err = -ENOBUFS;
			goto out;
		}
		pad_packet(dp, user_skb);
	}

	/* Add OVS_PACKET_ATTR_LEN when packet is truncated */
	if (cutlen > 0) {
		if (nla_put_u32(user_skb, OVS_PACKET_ATTR_LEN,
				skb->len)) {
			err = -ENOBUFS;
			goto out;
		}
		pad_packet(dp, user_skb);
	}

	/* Only reserve room for attribute header, packet data is added
	 * in skb_zerocopy() */
	if (!(nla = nla_reserve(user_skb, OVS_PACKET_ATTR_PACKET, 0))) {
		err = -ENOBUFS;
		goto out;
	}
	nla->nla_len = nla_attr_size(skb->len - cutlen);

	err = skb_zerocopy(user_skb, skb, skb->len - cutlen, hlen);
	if (err)
		goto out;

	/* Pad OVS_PACKET_ATTR_PACKET if linear copy was performed */
	pad_packet(dp, user_skb);

	((struct nlmsghdr *) user_skb->data)->nlmsg_len = user_skb->len;

	err = genlmsg_unicast(ovs_dp_get_net(dp), user_skb, upcall_info->portid);
	user_skb = NULL;
out:
	if (err)
		skb_tx_error(skb);
	kfree_skb(user_skb);
	kfree_skb(nskb);
	return err;
}
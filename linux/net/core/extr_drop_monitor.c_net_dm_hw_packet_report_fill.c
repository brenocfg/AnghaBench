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
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  len; int /*<<< orphan*/  tstamp; } ;
struct nlattr {int /*<<< orphan*/  nla_len; int /*<<< orphan*/  nla_type; } ;
struct net_dm_hw_metadata {struct net_device* input_dev; int /*<<< orphan*/  trap_name; int /*<<< orphan*/  trap_group_name; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {struct net_dm_hw_metadata* hw_metadata; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NET_DM_ATTR_HW_TRAP_GROUP_NAME ; 
 int /*<<< orphan*/  NET_DM_ATTR_HW_TRAP_NAME ; 
 int /*<<< orphan*/  NET_DM_ATTR_ORIGIN ; 
 int /*<<< orphan*/  NET_DM_ATTR_ORIG_LEN ; 
 int /*<<< orphan*/  NET_DM_ATTR_PAD ; 
 int /*<<< orphan*/  NET_DM_ATTR_PAYLOAD ; 
 int /*<<< orphan*/  NET_DM_ATTR_PROTO ; 
 int /*<<< orphan*/  NET_DM_ATTR_TIMESTAMP ; 
 int /*<<< orphan*/  NET_DM_CMD_PACKET_ALERT ; 
 int /*<<< orphan*/  NET_DM_ORIGIN_HW ; 
 TYPE_1__* NET_DM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 
 int net_dm_packet_report_in_port_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_drop_monitor_family ; 
 int /*<<< orphan*/  nla_attr_size (size_t) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_put_string (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_total_size (size_t) ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct nlattr* skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_dm_hw_packet_report_fill(struct sk_buff *msg,
					struct sk_buff *skb, size_t payload_len)
{
	struct net_dm_hw_metadata *hw_metadata;
	struct nlattr *attr;
	void *hdr;

	hw_metadata = NET_DM_SKB_CB(skb)->hw_metadata;

	hdr = genlmsg_put(msg, 0, 0, &net_drop_monitor_family, 0,
			  NET_DM_CMD_PACKET_ALERT);
	if (!hdr)
		return -EMSGSIZE;

	if (nla_put_u16(msg, NET_DM_ATTR_ORIGIN, NET_DM_ORIGIN_HW))
		goto nla_put_failure;

	if (nla_put_string(msg, NET_DM_ATTR_HW_TRAP_GROUP_NAME,
			   hw_metadata->trap_group_name))
		goto nla_put_failure;

	if (nla_put_string(msg, NET_DM_ATTR_HW_TRAP_NAME,
			   hw_metadata->trap_name))
		goto nla_put_failure;

	if (hw_metadata->input_dev) {
		struct net_device *dev = hw_metadata->input_dev;
		int rc;

		rc = net_dm_packet_report_in_port_put(msg, dev->ifindex,
						      dev->name);
		if (rc)
			goto nla_put_failure;
	}

	if (nla_put_u64_64bit(msg, NET_DM_ATTR_TIMESTAMP,
			      ktime_to_ns(skb->tstamp), NET_DM_ATTR_PAD))
		goto nla_put_failure;

	if (nla_put_u32(msg, NET_DM_ATTR_ORIG_LEN, skb->len))
		goto nla_put_failure;

	if (!payload_len)
		goto out;

	if (nla_put_u16(msg, NET_DM_ATTR_PROTO, be16_to_cpu(skb->protocol)))
		goto nla_put_failure;

	attr = skb_put(msg, nla_total_size(payload_len));
	attr->nla_type = NET_DM_ATTR_PAYLOAD;
	attr->nla_len = nla_attr_size(payload_len);
	if (skb_copy_bits(skb, 0, nla_data(attr), payload_len))
		goto nla_put_failure;

out:
	genlmsg_end(msg, hdr);

	return 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	return -EMSGSIZE;
}
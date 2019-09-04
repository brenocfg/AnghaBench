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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct psample_group {int /*<<< orphan*/  net; int /*<<< orphan*/  seq; int /*<<< orphan*/  group_num; } ;
struct nlattr {int /*<<< orphan*/  nla_len; int /*<<< orphan*/  nla_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NLA_ALIGNTO ; 
 int NLA_HDRLEN ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_DATA ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_GROUP_SEQ ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_IIFINDEX ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_OIFINDEX ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_ORIGSIZE ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_SAMPLE_GROUP ; 
 int /*<<< orphan*/  PSAMPLE_ATTR_SAMPLE_RATE ; 
 int /*<<< orphan*/  PSAMPLE_CMD_SAMPLE ; 
 int PSAMPLE_MAX_PACKET_SIZE ; 
 int /*<<< orphan*/  PSAMPLE_NL_MCGRP_SAMPLE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast_netns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* genlmsg_new (int,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_attr_size (int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 int nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nla_total_size (int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*) ; 
 int /*<<< orphan*/  psample_nl_family ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct nlattr* skb_put (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int) ; 

void psample_sample_packet(struct psample_group *group, struct sk_buff *skb,
			   u32 trunc_size, int in_ifindex, int out_ifindex,
			   u32 sample_rate)
{
	struct sk_buff *nl_skb;
	int data_len;
	int meta_len;
	void *data;
	int ret;

	meta_len = (in_ifindex ? nla_total_size(sizeof(u16)) : 0) +
		   (out_ifindex ? nla_total_size(sizeof(u16)) : 0) +
		   nla_total_size(sizeof(u32)) +	/* sample_rate */
		   nla_total_size(sizeof(u32)) +	/* orig_size */
		   nla_total_size(sizeof(u32)) +	/* group_num */
		   nla_total_size(sizeof(u32));		/* seq */

	data_len = min(skb->len, trunc_size);
	if (meta_len + nla_total_size(data_len) > PSAMPLE_MAX_PACKET_SIZE)
		data_len = PSAMPLE_MAX_PACKET_SIZE - meta_len - NLA_HDRLEN
			    - NLA_ALIGNTO;

	nl_skb = genlmsg_new(meta_len + data_len, GFP_ATOMIC);
	if (unlikely(!nl_skb))
		return;

	data = genlmsg_put(nl_skb, 0, 0, &psample_nl_family, 0,
			   PSAMPLE_CMD_SAMPLE);
	if (unlikely(!data))
		goto error;

	if (in_ifindex) {
		ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_IIFINDEX, in_ifindex);
		if (unlikely(ret < 0))
			goto error;
	}

	if (out_ifindex) {
		ret = nla_put_u16(nl_skb, PSAMPLE_ATTR_OIFINDEX, out_ifindex);
		if (unlikely(ret < 0))
			goto error;
	}

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_SAMPLE_RATE, sample_rate);
	if (unlikely(ret < 0))
		goto error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_ORIGSIZE, skb->len);
	if (unlikely(ret < 0))
		goto error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_SAMPLE_GROUP, group->group_num);
	if (unlikely(ret < 0))
		goto error;

	ret = nla_put_u32(nl_skb, PSAMPLE_ATTR_GROUP_SEQ, group->seq++);
	if (unlikely(ret < 0))
		goto error;

	if (data_len) {
		int nla_len = nla_total_size(data_len);
		struct nlattr *nla;

		nla = skb_put(nl_skb, nla_len);
		nla->nla_type = PSAMPLE_ATTR_DATA;
		nla->nla_len = nla_attr_size(data_len);

		if (skb_copy_bits(skb, 0, nla_data(nla), data_len))
			goto error;
	}

	genlmsg_end(nl_skb, data);
	genlmsg_multicast_netns(&psample_nl_family, group->net, nl_skb, 0,
				PSAMPLE_NL_MCGRP_SAMPLE, GFP_ATOMIC);

	return;
error:
	pr_err_ratelimited("Could not create psample log message\n");
	nlmsg_free(nl_skb);
}
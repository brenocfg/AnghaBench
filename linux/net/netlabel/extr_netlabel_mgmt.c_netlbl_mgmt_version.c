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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NETLBL_PROTO_VERSION ; 
 int /*<<< orphan*/  NLBL_MGMT_A_VERSION ; 
 int /*<<< orphan*/  NLBL_MGMT_C_VERSION ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlbl_mgmt_gnl_family ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_mgmt_version(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val = -ENOMEM;
	struct sk_buff *ans_skb = NULL;
	void *data;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (ans_skb == NULL)
		return -ENOMEM;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_mgmt_gnl_family,
				 0, NLBL_MGMT_C_VERSION);
	if (data == NULL)
		goto version_failure;

	ret_val = nla_put_u32(ans_skb,
			      NLBL_MGMT_A_VERSION,
			      NETLBL_PROTO_VERSION);
	if (ret_val != 0)
		goto version_failure;

	genlmsg_end(ans_skb, data);
	return genlmsg_reply(ans_skb, info);

version_failure:
	kfree_skb(ans_skb);
	return ret_val;
}
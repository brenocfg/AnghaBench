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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct netlbl_dom_map {int dummy; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NLBL_MGMT_A_FAMILY ; 
 int /*<<< orphan*/  NLBL_MGMT_C_LISTDEF ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct netlbl_dom_map* netlbl_domhsh_getentry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlbl_mgmt_gnl_family ; 
 int netlbl_mgmt_listentry (struct sk_buff*,struct netlbl_dom_map*) ; 
 int /*<<< orphan*/  nla_get_u16 (scalar_t__) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int netlbl_mgmt_listdef(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val = -ENOMEM;
	struct sk_buff *ans_skb = NULL;
	void *data;
	struct netlbl_dom_map *entry;
	u16 family;

	if (info->attrs[NLBL_MGMT_A_FAMILY])
		family = nla_get_u16(info->attrs[NLBL_MGMT_A_FAMILY]);
	else
		family = AF_INET;

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (ans_skb == NULL)
		return -ENOMEM;
	data = genlmsg_put_reply(ans_skb, info, &netlbl_mgmt_gnl_family,
				 0, NLBL_MGMT_C_LISTDEF);
	if (data == NULL)
		goto listdef_failure;

	rcu_read_lock();
	entry = netlbl_domhsh_getentry(NULL, family);
	if (entry == NULL) {
		ret_val = -ENOENT;
		goto listdef_failure_lock;
	}
	ret_val = netlbl_mgmt_listentry(ans_skb, entry);
	rcu_read_unlock();
	if (ret_val != 0)
		goto listdef_failure;

	genlmsg_end(ans_skb, data);
	return genlmsg_reply(ans_skb, info);

listdef_failure_lock:
	rcu_read_unlock();
listdef_failure:
	kfree_skb(ans_skb);
	return ret_val;
}
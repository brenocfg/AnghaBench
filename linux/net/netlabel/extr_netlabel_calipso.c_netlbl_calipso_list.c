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
struct genl_info {int /*<<< orphan*/ * attrs; } ;
struct calipso_doi {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NLBL_CALIPSO_A_DOI ; 
 int /*<<< orphan*/  NLBL_CALIPSO_A_MTYPE ; 
 int /*<<< orphan*/  NLBL_CALIPSO_C_LIST ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 struct calipso_doi* calipso_doi_getdef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calipso_doi_putdef (struct calipso_doi*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netlbl_calipso_gnl_family ; 
 int /*<<< orphan*/  nla_get_u32 (int /*<<< orphan*/ ) ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_calipso_list(struct sk_buff *skb, struct genl_info *info)
{
	int ret_val;
	struct sk_buff *ans_skb = NULL;
	void *data;
	u32 doi;
	struct calipso_doi *doi_def;

	if (!info->attrs[NLBL_CALIPSO_A_DOI]) {
		ret_val = -EINVAL;
		goto list_failure;
	}

	doi = nla_get_u32(info->attrs[NLBL_CALIPSO_A_DOI]);

	doi_def = calipso_doi_getdef(doi);
	if (!doi_def) {
		ret_val = -EINVAL;
		goto list_failure;
	}

	ans_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!ans_skb) {
		ret_val = -ENOMEM;
		goto list_failure_put;
	}
	data = genlmsg_put_reply(ans_skb, info, &netlbl_calipso_gnl_family,
				 0, NLBL_CALIPSO_C_LIST);
	if (!data) {
		ret_val = -ENOMEM;
		goto list_failure_put;
	}

	ret_val = nla_put_u32(ans_skb, NLBL_CALIPSO_A_MTYPE, doi_def->type);
	if (ret_val != 0)
		goto list_failure_put;

	calipso_doi_putdef(doi_def);

	genlmsg_end(ans_skb, data);
	return genlmsg_reply(ans_skb, info);

list_failure_put:
	calipso_doi_putdef(doi_def);
list_failure:
	kfree_skb(ans_skb);
	return ret_val;
}
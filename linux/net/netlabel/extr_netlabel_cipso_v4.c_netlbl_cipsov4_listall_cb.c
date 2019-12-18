#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct netlbl_cipsov4_doiwalk_arg {int /*<<< orphan*/  skb; int /*<<< orphan*/  seq; TYPE_1__* nl_cb; } ;
struct cipso_v4_doi {int /*<<< orphan*/  type; int /*<<< orphan*/  doi; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_DOI ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_A_MTYPE ; 
 int /*<<< orphan*/  NLBL_CIPSOV4_C_LISTALL ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  genlmsg_cancel (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  genlmsg_end (int /*<<< orphan*/ ,void*) ; 
 void* genlmsg_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlbl_cipsov4_gnl_family ; 
 int nla_put_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlbl_cipsov4_listall_cb(struct cipso_v4_doi *doi_def, void *arg)
{
	int ret_val = -ENOMEM;
	struct netlbl_cipsov4_doiwalk_arg *cb_arg = arg;
	void *data;

	data = genlmsg_put(cb_arg->skb, NETLINK_CB(cb_arg->nl_cb->skb).portid,
			   cb_arg->seq, &netlbl_cipsov4_gnl_family,
			   NLM_F_MULTI, NLBL_CIPSOV4_C_LISTALL);
	if (data == NULL)
		goto listall_cb_failure;

	ret_val = nla_put_u32(cb_arg->skb, NLBL_CIPSOV4_A_DOI, doi_def->doi);
	if (ret_val != 0)
		goto listall_cb_failure;
	ret_val = nla_put_u32(cb_arg->skb,
			      NLBL_CIPSOV4_A_MTYPE,
			      doi_def->type);
	if (ret_val != 0)
		goto listall_cb_failure;

	genlmsg_end(cb_arg->skb, data);
	return 0;

listall_cb_failure:
	genlmsg_cancel(cb_arg->skb, data);
	return ret_val;
}
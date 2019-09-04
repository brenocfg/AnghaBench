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
struct tcf_proto {int /*<<< orphan*/  root; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;
struct basic_head {int /*<<< orphan*/  flist; int /*<<< orphan*/  handle_idr; } ;
struct basic_filter {int handle; int /*<<< orphan*/  exts; int /*<<< orphan*/  link; int /*<<< orphan*/  rwork; int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INT_MAX ; 
 int /*<<< orphan*/  TCA_BASIC_ACT ; 
 int /*<<< orphan*/  TCA_BASIC_MAX ; 
 int /*<<< orphan*/  TCA_BASIC_POLICE ; 
 size_t TCA_OPTIONS ; 
 size_t TCA_RATE ; 
 int /*<<< orphan*/  basic_delete_filter_work ; 
 int /*<<< orphan*/  basic_policy ; 
 int basic_set_parms (struct net*,struct tcf_proto*,struct basic_filter*,unsigned long,struct nlattr**,struct nlattr*,int,struct netlink_ext_ack*) ; 
 int idr_alloc_u32 (int /*<<< orphan*/ *,struct basic_filter*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,struct basic_filter*,int) ; 
 int /*<<< orphan*/  kfree (struct basic_filter*) ; 
 struct basic_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nla_parse_nested (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct basic_head* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_exts_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcf_exts_get_net (int /*<<< orphan*/ *) ; 
 int tcf_exts_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_unbind_filter (struct tcf_proto*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int basic_change(struct net *net, struct sk_buff *in_skb,
			struct tcf_proto *tp, unsigned long base, u32 handle,
			struct nlattr **tca, void **arg, bool ovr,
			struct netlink_ext_ack *extack)
{
	int err;
	struct basic_head *head = rtnl_dereference(tp->root);
	struct nlattr *tb[TCA_BASIC_MAX + 1];
	struct basic_filter *fold = (struct basic_filter *) *arg;
	struct basic_filter *fnew;

	if (tca[TCA_OPTIONS] == NULL)
		return -EINVAL;

	err = nla_parse_nested(tb, TCA_BASIC_MAX, tca[TCA_OPTIONS],
			       basic_policy, NULL);
	if (err < 0)
		return err;

	if (fold != NULL) {
		if (handle && fold->handle != handle)
			return -EINVAL;
	}

	fnew = kzalloc(sizeof(*fnew), GFP_KERNEL);
	if (!fnew)
		return -ENOBUFS;

	err = tcf_exts_init(&fnew->exts, TCA_BASIC_ACT, TCA_BASIC_POLICE);
	if (err < 0)
		goto errout;

	if (!handle) {
		handle = 1;
		err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
				    INT_MAX, GFP_KERNEL);
	} else if (!fold) {
		err = idr_alloc_u32(&head->handle_idr, fnew, &handle,
				    handle, GFP_KERNEL);
	}
	if (err)
		goto errout;
	fnew->handle = handle;

	err = basic_set_parms(net, tp, fnew, base, tb, tca[TCA_RATE], ovr,
			      extack);
	if (err < 0) {
		if (!fold)
			idr_remove(&head->handle_idr, fnew->handle);
		goto errout;
	}

	*arg = fnew;

	if (fold) {
		idr_replace(&head->handle_idr, fnew, fnew->handle);
		list_replace_rcu(&fold->link, &fnew->link);
		tcf_unbind_filter(tp, &fold->res);
		tcf_exts_get_net(&fold->exts);
		tcf_queue_work(&fold->rwork, basic_delete_filter_work);
	} else {
		list_add_rcu(&fnew->link, &head->flist);
	}

	return 0;
errout:
	tcf_exts_destroy(&fnew->exts);
	kfree(fnew);
	return err;
}
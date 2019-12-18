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
struct tcf_proto {int dummy; } ;
struct tc_cookie {struct tc_cookie* data; } ;
struct tc_action_ops {int (* init ) (struct net*,struct nlattr*,struct nlattr*,struct tc_action**,int,int,int,struct tcf_proto*,struct netlink_ext_ack*) ;int /*<<< orphan*/  owner; } ;
struct tc_action {int /*<<< orphan*/  goto_chain; int /*<<< orphan*/  tcfa_action; int /*<<< orphan*/  act_cookie; } ;
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ACT_P_CREATED ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct tc_action* ERR_PTR (int) ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 size_t TCA_ACT_COOKIE ; 
 size_t TCA_ACT_KIND ; 
 int /*<<< orphan*/  TCA_ACT_MAX ; 
 size_t TCA_ACT_OPTIONS ; 
 scalar_t__ TC_ACT_EXT_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_ACT_GOTO_CHAIN ; 
 int /*<<< orphan*/  kfree (struct tc_cookie*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 struct tc_cookie* nla_memdup_cookie (struct nlattr**) ; 
 int nla_parse_nested_deprecated (struct nlattr**,int /*<<< orphan*/ ,struct nlattr*,int /*<<< orphan*/ ,struct netlink_ext_ack*) ; 
 int nla_strlcpy (char*,struct nlattr*,int) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int strlcpy (char*,char*,int) ; 
 int stub1 (struct net*,struct nlattr*,struct nlattr*,struct tc_action**,int,int,int,struct tcf_proto*,struct netlink_ext_ack*) ; 
 int stub2 (struct net*,struct nlattr*,struct nlattr*,struct tc_action**,int,int,int,struct tcf_proto*,struct netlink_ext_ack*) ; 
 struct tc_action_ops* tc_lookup_action_n (char*) ; 
 int /*<<< orphan*/  tcf_action_destroy_1 (struct tc_action*,int) ; 
 int /*<<< orphan*/  tcf_action_policy ; 
 int /*<<< orphan*/  tcf_set_action_cookie (int /*<<< orphan*/ *,struct tc_cookie*) ; 

struct tc_action *tcf_action_init_1(struct net *net, struct tcf_proto *tp,
				    struct nlattr *nla, struct nlattr *est,
				    char *name, int ovr, int bind,
				    bool rtnl_held,
				    struct netlink_ext_ack *extack)
{
	struct tc_action *a;
	struct tc_action_ops *a_o;
	struct tc_cookie *cookie = NULL;
	char act_name[IFNAMSIZ];
	struct nlattr *tb[TCA_ACT_MAX + 1];
	struct nlattr *kind;
	int err;

	if (name == NULL) {
		err = nla_parse_nested_deprecated(tb, TCA_ACT_MAX, nla,
						  tcf_action_policy, extack);
		if (err < 0)
			goto err_out;
		err = -EINVAL;
		kind = tb[TCA_ACT_KIND];
		if (!kind) {
			NL_SET_ERR_MSG(extack, "TC action kind must be specified");
			goto err_out;
		}
		if (nla_strlcpy(act_name, kind, IFNAMSIZ) >= IFNAMSIZ) {
			NL_SET_ERR_MSG(extack, "TC action name too long");
			goto err_out;
		}
		if (tb[TCA_ACT_COOKIE]) {
			cookie = nla_memdup_cookie(tb);
			if (!cookie) {
				NL_SET_ERR_MSG(extack, "No memory to generate TC cookie");
				err = -ENOMEM;
				goto err_out;
			}
		}
	} else {
		if (strlcpy(act_name, name, IFNAMSIZ) >= IFNAMSIZ) {
			NL_SET_ERR_MSG(extack, "TC action name too long");
			err = -EINVAL;
			goto err_out;
		}
	}

	a_o = tc_lookup_action_n(act_name);
	if (a_o == NULL) {
#ifdef CONFIG_MODULES
		if (rtnl_held)
			rtnl_unlock();
		request_module("act_%s", act_name);
		if (rtnl_held)
			rtnl_lock();

		a_o = tc_lookup_action_n(act_name);

		/* We dropped the RTNL semaphore in order to
		 * perform the module load.  So, even if we
		 * succeeded in loading the module we have to
		 * tell the caller to replay the request.  We
		 * indicate this using -EAGAIN.
		 */
		if (a_o != NULL) {
			err = -EAGAIN;
			goto err_mod;
		}
#endif
		NL_SET_ERR_MSG(extack, "Failed to load TC action module");
		err = -ENOENT;
		goto err_out;
	}

	/* backward compatibility for policer */
	if (name == NULL)
		err = a_o->init(net, tb[TCA_ACT_OPTIONS], est, &a, ovr, bind,
				rtnl_held, tp, extack);
	else
		err = a_o->init(net, nla, est, &a, ovr, bind, rtnl_held,
				tp, extack);
	if (err < 0)
		goto err_mod;

	if (!name && tb[TCA_ACT_COOKIE])
		tcf_set_action_cookie(&a->act_cookie, cookie);

	/* module count goes up only when brand new policy is created
	 * if it exists and is only bound to in a_o->init() then
	 * ACT_P_CREATED is not returned (a zero is).
	 */
	if (err != ACT_P_CREATED)
		module_put(a_o->owner);

	if (TC_ACT_EXT_CMP(a->tcfa_action, TC_ACT_GOTO_CHAIN) &&
	    !rcu_access_pointer(a->goto_chain)) {
		tcf_action_destroy_1(a, bind);
		NL_SET_ERR_MSG(extack, "can't use goto chain with NULL chain");
		return ERR_PTR(-EINVAL);
	}

	return a;

err_mod:
	module_put(a_o->owner);
err_out:
	if (cookie) {
		kfree(cookie->data);
		kfree(cookie);
	}
	return ERR_PTR(err);
}
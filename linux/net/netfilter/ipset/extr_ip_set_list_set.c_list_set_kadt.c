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
struct xt_action_param {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ip_set_ext {int dummy; } ;
struct ip_set_adt_opt {int dummy; } ;
struct ip_set {int dummy; } ;
typedef  enum ipset_adt { ____Placeholder_ipset_adt } ipset_adt ;

/* Variables and functions */
 int EINVAL ; 
#define  IPSET_ADD 130 
#define  IPSET_DEL 129 
#define  IPSET_TEST 128 
 struct ip_set_ext IP_SET_INIT_KEXT (struct sk_buff const*,struct ip_set_adt_opt*,struct ip_set*) ; 
 int list_set_kadd (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,struct ip_set_adt_opt*,struct ip_set_ext*) ; 
 int list_set_kdel (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,struct ip_set_adt_opt*,struct ip_set_ext*) ; 
 int list_set_ktest (struct ip_set*,struct sk_buff const*,struct xt_action_param const*,struct ip_set_adt_opt*,struct ip_set_ext*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int
list_set_kadt(struct ip_set *set, const struct sk_buff *skb,
	      const struct xt_action_param *par,
	      enum ipset_adt adt, struct ip_set_adt_opt *opt)
{
	struct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	int ret = -EINVAL;

	rcu_read_lock();
	switch (adt) {
	case IPSET_TEST:
		ret = list_set_ktest(set, skb, par, opt, &ext);
		break;
	case IPSET_ADD:
		ret = list_set_kadd(set, skb, par, opt, &ext);
		break;
	case IPSET_DEL:
		ret = list_set_kdel(set, skb, par, opt, &ext);
		break;
	default:
		break;
	}
	rcu_read_unlock();

	return ret;
}
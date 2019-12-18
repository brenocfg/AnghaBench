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
typedef  size_t u16 ;
struct netlink_ext_ack {int dummy; } ;
struct lwtunnel_encap_ops {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t LWTUNNEL_ENCAP_MAX ; 
 size_t LWTUNNEL_ENCAP_NONE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  __rtnl_unlock () ; 
 int /*<<< orphan*/ * lwtun_encaps ; 
 char* lwtunnel_encap_str (size_t) ; 
 struct lwtunnel_encap_ops* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 

int lwtunnel_valid_encap_type(u16 encap_type, struct netlink_ext_ack *extack)
{
	const struct lwtunnel_encap_ops *ops;
	int ret = -EINVAL;

	if (encap_type == LWTUNNEL_ENCAP_NONE ||
	    encap_type > LWTUNNEL_ENCAP_MAX) {
		NL_SET_ERR_MSG(extack, "Unknown lwt encapsulation type");
		return ret;
	}

	rcu_read_lock();
	ops = rcu_dereference(lwtun_encaps[encap_type]);
	rcu_read_unlock();
#ifdef CONFIG_MODULES
	if (!ops) {
		const char *encap_type_str = lwtunnel_encap_str(encap_type);

		if (encap_type_str) {
			__rtnl_unlock();
			request_module("rtnl-lwt-%s", encap_type_str);
			rtnl_lock();

			rcu_read_lock();
			ops = rcu_dereference(lwtun_encaps[encap_type]);
			rcu_read_unlock();
		}
	}
#endif
	ret = ops ? 0 : -EOPNOTSUPP;
	if (ret < 0)
		NL_SET_ERR_MSG(extack, "lwt encapsulation type not supported");

	return ret;
}
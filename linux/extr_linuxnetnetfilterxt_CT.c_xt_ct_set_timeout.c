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
struct xt_tgchk_param {int dummy; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int
xt_ct_set_timeout(struct nf_conn *ct, const struct xt_tgchk_param *par,
		  const char *timeout_name)
{
#ifdef CONFIG_NF_CONNTRACK_TIMEOUT
	typeof(nf_ct_timeout_find_get_hook) timeout_find_get;
	const struct nf_conntrack_l4proto *l4proto;
	struct nf_ct_timeout *timeout;
	struct nf_conn_timeout *timeout_ext;
	const char *errmsg = NULL;
	int ret = 0;
	u8 proto;

	rcu_read_lock();
	timeout_find_get = rcu_dereference(nf_ct_timeout_find_get_hook);
	if (timeout_find_get == NULL) {
		ret = -ENOENT;
		errmsg = "Timeout policy base is empty";
		goto out;
	}

	proto = xt_ct_find_proto(par);
	if (!proto) {
		ret = -EINVAL;
		errmsg = "You must specify a L4 protocol and not use inversions on it";
		goto out;
	}

	timeout = timeout_find_get(par->net, timeout_name);
	if (timeout == NULL) {
		ret = -ENOENT;
		pr_info_ratelimited("No such timeout policy \"%s\"\n",
				    timeout_name);
		goto out;
	}

	if (timeout->l3num != par->family) {
		ret = -EINVAL;
		pr_info_ratelimited("Timeout policy `%s' can only be used by L%d protocol number %d\n",
				    timeout_name, 3, timeout->l3num);
		goto err_put_timeout;
	}
	/* Make sure the timeout policy matches any existing protocol tracker,
	 * otherwise default to generic.
	 */
	l4proto = __nf_ct_l4proto_find(par->family, proto);
	if (timeout->l4proto->l4proto != l4proto->l4proto) {
		ret = -EINVAL;
		pr_info_ratelimited("Timeout policy `%s' can only be used by L%d protocol number %d\n",
				    timeout_name, 4, timeout->l4proto->l4proto);
		goto err_put_timeout;
	}
	timeout_ext = nf_ct_timeout_ext_add(ct, timeout, GFP_ATOMIC);
	if (!timeout_ext) {
		ret = -ENOMEM;
		goto err_put_timeout;
	}

	rcu_read_unlock();
	return ret;

err_put_timeout:
	__xt_ct_tg_timeout_put(timeout);
out:
	rcu_read_unlock();
	if (errmsg)
		pr_info_ratelimited("%s\n", errmsg);
	return ret;
#else
	return -EOPNOTSUPP;
#endif
}
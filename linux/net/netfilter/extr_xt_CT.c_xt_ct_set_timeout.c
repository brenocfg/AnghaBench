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
typedef  int /*<<< orphan*/  u8 ;
struct xt_tgchk_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; } ;
struct nf_conntrack_l4proto {int /*<<< orphan*/  l4proto; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct nf_conntrack_l4proto* nf_ct_l4proto_find (int /*<<< orphan*/ ) ; 
 int nf_ct_set_timeout (int /*<<< orphan*/ ,struct nf_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*) ; 
 int /*<<< orphan*/  xt_ct_find_proto (struct xt_tgchk_param const*) ; 

__attribute__((used)) static int
xt_ct_set_timeout(struct nf_conn *ct, const struct xt_tgchk_param *par,
		  const char *timeout_name)
{
#ifdef CONFIG_NF_CONNTRACK_TIMEOUT
	const struct nf_conntrack_l4proto *l4proto;
	u8 proto;

	proto = xt_ct_find_proto(par);
	if (!proto) {
		pr_info_ratelimited("You must specify a L4 protocol and not "
				    "use inversions on it");
		return -EINVAL;
	}
	l4proto = nf_ct_l4proto_find(proto);
	return nf_ct_set_timeout(par->net, ct, par->family, l4proto->l4proto,
				 timeout_name);

#else
	return -EOPNOTSUPP;
#endif
}
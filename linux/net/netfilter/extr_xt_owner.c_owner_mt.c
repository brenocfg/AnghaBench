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
struct xt_owner_match_info {int match; int invert; int /*<<< orphan*/  gid_max; int /*<<< orphan*/  gid_min; int /*<<< orphan*/  uid_max; int /*<<< orphan*/  uid_min; } ;
struct xt_action_param {struct xt_owner_match_info* matchinfo; } ;
struct sock {TYPE_1__* sk_socket; } ;
struct sk_buff {int dummy; } ;
struct net {int /*<<< orphan*/  user_ns; } ;
struct group_info {unsigned int ngroups; int /*<<< orphan*/ * gid; } ;
struct file {TYPE_2__* f_cred; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;
struct TYPE_4__ {int /*<<< orphan*/  fsgid; struct group_info* group_info; int /*<<< orphan*/  fsuid; } ;
struct TYPE_3__ {struct file* file; } ;

/* Variables and functions */
 int XT_OWNER_GID ; 
 int XT_OWNER_SOCKET ; 
 int XT_OWNER_SUPPL_GROUPS ; 
 int XT_OWNER_UID ; 
 scalar_t__ gid_gte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gid_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 struct sock* skb_to_full_sk (struct sk_buff const*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 scalar_t__ uid_gte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net* xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool
owner_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_owner_match_info *info = par->matchinfo;
	const struct file *filp;
	struct sock *sk = skb_to_full_sk(skb);
	struct net *net = xt_net(par);

	if (!sk || !sk->sk_socket || !net_eq(net, sock_net(sk)))
		return (info->match ^ info->invert) == 0;
	else if (info->match & info->invert & XT_OWNER_SOCKET)
		/*
		 * Socket exists but user wanted ! --socket-exists.
		 * (Single ampersands intended.)
		 */
		return false;

	filp = sk->sk_socket->file;
	if (filp == NULL)
		return ((info->match ^ info->invert) &
		       (XT_OWNER_UID | XT_OWNER_GID)) == 0;

	if (info->match & XT_OWNER_UID) {
		kuid_t uid_min = make_kuid(net->user_ns, info->uid_min);
		kuid_t uid_max = make_kuid(net->user_ns, info->uid_max);
		if ((uid_gte(filp->f_cred->fsuid, uid_min) &&
		     uid_lte(filp->f_cred->fsuid, uid_max)) ^
		    !(info->invert & XT_OWNER_UID))
			return false;
	}

	if (info->match & XT_OWNER_GID) {
		unsigned int i, match = false;
		kgid_t gid_min = make_kgid(net->user_ns, info->gid_min);
		kgid_t gid_max = make_kgid(net->user_ns, info->gid_max);
		struct group_info *gi = filp->f_cred->group_info;

		if (gid_gte(filp->f_cred->fsgid, gid_min) &&
		    gid_lte(filp->f_cred->fsgid, gid_max))
			match = true;

		if (!match && (info->match & XT_OWNER_SUPPL_GROUPS) && gi) {
			for (i = 0; i < gi->ngroups; ++i) {
				kgid_t group = gi->gid[i];

				if (gid_gte(group, gid_min) &&
				    gid_lte(group, gid_max)) {
					match = true;
					break;
				}
			}
		}

		if (match ^ !(info->invert & XT_OWNER_GID))
			return false;
	}

	return true;
}
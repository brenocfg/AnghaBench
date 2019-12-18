#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sock {int /*<<< orphan*/  sk_protocol; struct sk_security_struct* sk_security; } ;
struct sk_security_struct {int sclass; } ;
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {int /*<<< orphan*/  nlmsg_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ NLMSG_HDRLEN ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  enforcing_enabled (int /*<<< orphan*/ *) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* secclass_map ; 
 scalar_t__ security_get_allow_unknown (int /*<<< orphan*/ *) ; 
 int selinux_nlmsg_lookup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 
 int sock_has_perm (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 

__attribute__((used)) static int selinux_nlmsg_perm(struct sock *sk, struct sk_buff *skb)
{
	int err = 0;
	u32 perm;
	struct nlmsghdr *nlh;
	struct sk_security_struct *sksec = sk->sk_security;

	if (skb->len < NLMSG_HDRLEN) {
		err = -EINVAL;
		goto out;
	}
	nlh = nlmsg_hdr(skb);

	err = selinux_nlmsg_lookup(sksec->sclass, nlh->nlmsg_type, &perm);
	if (err) {
		if (err == -EINVAL) {
			pr_warn_ratelimited("SELinux: unrecognized netlink"
			       " message: protocol=%hu nlmsg_type=%hu sclass=%s"
			       " pig=%d comm=%s\n",
			       sk->sk_protocol, nlh->nlmsg_type,
			       secclass_map[sksec->sclass - 1].name,
			       task_pid_nr(current), current->comm);
			if (!enforcing_enabled(&selinux_state) ||
			    security_get_allow_unknown(&selinux_state))
				err = 0;
		}

		/* Ignore */
		if (err == -ENOENT)
			err = 0;
		goto out;
	}

	err = sock_has_perm(sk, perm);
out:
	return err;
}
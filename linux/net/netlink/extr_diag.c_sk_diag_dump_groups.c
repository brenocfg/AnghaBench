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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct netlink_sock {int /*<<< orphan*/ * groups; int /*<<< orphan*/  ngroups; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLINK_DIAG_GROUPS ; 
 int /*<<< orphan*/  NLGRPSZ (int /*<<< orphan*/ ) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump_groups(struct sock *sk, struct sk_buff *nlskb)
{
	struct netlink_sock *nlk = nlk_sk(sk);

	if (nlk->groups == NULL)
		return 0;

	return nla_put(nlskb, NETLINK_DIAG_GROUPS, NLGRPSZ(nlk->ngroups),
		       nlk->groups);
}
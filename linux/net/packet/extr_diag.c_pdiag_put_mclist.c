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
struct sk_buff {int dummy; } ;
struct packet_sock {struct packet_mclist* mclist; } ;
struct packet_mclist {int /*<<< orphan*/  addr; int /*<<< orphan*/  count; int /*<<< orphan*/  alen; int /*<<< orphan*/  type; int /*<<< orphan*/  ifindex; struct packet_mclist* next; } ;
struct packet_diag_mclist {int /*<<< orphan*/  pdmc_addr; int /*<<< orphan*/  pdmc_count; int /*<<< orphan*/  pdmc_alen; int /*<<< orphan*/  pdmc_type; int /*<<< orphan*/  pdmc_index; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  PACKET_DIAG_MCLIST ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct packet_diag_mclist* nla_reserve_nohdr (struct sk_buff*,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static int pdiag_put_mclist(const struct packet_sock *po, struct sk_buff *nlskb)
{
	struct nlattr *mca;
	struct packet_mclist *ml;

	mca = nla_nest_start_noflag(nlskb, PACKET_DIAG_MCLIST);
	if (!mca)
		return -EMSGSIZE;

	rtnl_lock();
	for (ml = po->mclist; ml; ml = ml->next) {
		struct packet_diag_mclist *dml;

		dml = nla_reserve_nohdr(nlskb, sizeof(*dml));
		if (!dml) {
			rtnl_unlock();
			nla_nest_cancel(nlskb, mca);
			return -EMSGSIZE;
		}

		dml->pdmc_index = ml->ifindex;
		dml->pdmc_type = ml->type;
		dml->pdmc_alen = ml->alen;
		dml->pdmc_count = ml->count;
		BUILD_BUG_ON(sizeof(dml->pdmc_addr) != sizeof(ml->addr));
		memcpy(dml->pdmc_addr, ml->addr, sizeof(ml->addr));
	}

	rtnl_unlock();
	nla_nest_end(nlskb, mca);

	return 0;
}
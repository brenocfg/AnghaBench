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
struct nlattr {int dummy; } ;
struct nf_conn_synproxy {int /*<<< orphan*/  tsoff; int /*<<< orphan*/  its; int /*<<< orphan*/  isn; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_SYNPROXY ; 
 int /*<<< orphan*/  CTA_SYNPROXY_ISN ; 
 int /*<<< orphan*/  CTA_SYNPROXY_ITS ; 
 int /*<<< orphan*/  CTA_SYNPROXY_TSOFF ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 struct nf_conn_synproxy* nfct_synproxy (struct nf_conn*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_be32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ctnetlink_dump_ct_synproxy(struct sk_buff *skb, struct nf_conn *ct)
{
	struct nf_conn_synproxy *synproxy = nfct_synproxy(ct);
	struct nlattr *nest_parms;

	if (!synproxy)
		return 0;

	nest_parms = nla_nest_start(skb, CTA_SYNPROXY);
	if (!nest_parms)
		goto nla_put_failure;

	if (nla_put_be32(skb, CTA_SYNPROXY_ISN, htonl(synproxy->isn)) ||
	    nla_put_be32(skb, CTA_SYNPROXY_ITS, htonl(synproxy->its)) ||
	    nla_put_be32(skb, CTA_SYNPROXY_TSOFF, htonl(synproxy->tsoff)))
		goto nla_put_failure;

	nla_nest_end(skb, nest_parms);

	return 0;

nla_put_failure:
	return -1;
}
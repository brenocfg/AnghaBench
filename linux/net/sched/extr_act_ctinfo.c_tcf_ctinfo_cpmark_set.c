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
struct tcf_ctinfo_params {int cpmarkmask; } ;
struct tcf_ctinfo {int /*<<< orphan*/  stats_cpmark_set; } ;
struct sk_buff {int mark; } ;
struct nf_conn {int mark; } ;

/* Variables and functions */

__attribute__((used)) static void tcf_ctinfo_cpmark_set(struct nf_conn *ct, struct tcf_ctinfo *ca,
				  struct tcf_ctinfo_params *cp,
				  struct sk_buff *skb)
{
	ca->stats_cpmark_set++;
	skb->mark = ct->mark & cp->cpmarkmask;
}
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
struct tcf_proto {int dummy; } ;
struct tcf_chain_info {int /*<<< orphan*/ * pprev; } ;
struct tcf_chain {int dummy; } ;

/* Variables and functions */
 struct tcf_proto* tcf_chain_dereference (int /*<<< orphan*/ ,struct tcf_chain*) ; 

__attribute__((used)) static struct tcf_proto *tcf_chain_tp_prev(struct tcf_chain *chain,
					   struct tcf_chain_info *chain_info)
{
	return tcf_chain_dereference(*chain_info->pprev, chain);
}
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
struct tcf_pedit {struct tc_pedit_key* tcfp_keys_ex; struct tc_pedit_key* tcfp_keys; } ;
struct tc_pedit_key {int dummy; } ;
struct tc_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct tc_pedit_key*) ; 
 struct tcf_pedit* to_pedit (struct tc_action*) ; 

__attribute__((used)) static void tcf_pedit_cleanup(struct tc_action *a)
{
	struct tcf_pedit *p = to_pedit(a);
	struct tc_pedit_key *keys = p->tcfp_keys;

	kfree(keys);
	kfree(p->tcfp_keys_ex);
}
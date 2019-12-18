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
struct aa_policy {int /*<<< orphan*/  hname; int /*<<< orphan*/  list; int /*<<< orphan*/  profiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_BUG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aa_put_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_list_rcu (int /*<<< orphan*/ *) ; 

void aa_policy_destroy(struct aa_policy *policy)
{
	AA_BUG(on_list_rcu(&policy->profiles));
	AA_BUG(on_list_rcu(&policy->list));

	/* don't free name as its a subset of hname */
	aa_put_str(policy->hname);
}
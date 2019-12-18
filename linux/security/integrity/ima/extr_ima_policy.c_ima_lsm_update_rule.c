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
struct ima_rule_entry {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ima_rule_entry* ima_lsm_copy_rule (struct ima_rule_entry*) ; 
 int /*<<< orphan*/  ima_lsm_free_rule (struct ima_rule_entry*) ; 
 int /*<<< orphan*/  list_replace_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static int ima_lsm_update_rule(struct ima_rule_entry *entry)
{
	struct ima_rule_entry *nentry;

	nentry = ima_lsm_copy_rule(entry);
	if (!nentry)
		return -ENOMEM;

	list_replace_rcu(&entry->list, &nentry->list);
	synchronize_rcu();
	ima_lsm_free_rule(entry);

	return 0;
}
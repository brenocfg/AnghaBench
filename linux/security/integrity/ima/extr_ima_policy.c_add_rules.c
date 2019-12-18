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
struct ima_rule_entry {scalar_t__ action; scalar_t__ func; int /*<<< orphan*/  list; } ;
typedef  enum policy_rule_list { ____Placeholder_policy_rule_list } policy_rule_list ;

/* Variables and functions */
 scalar_t__ APPRAISE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IMA_APPRAISE_POLICY ; 
 int IMA_CUSTOM_POLICY ; 
 int IMA_DEFAULT_POLICY ; 
 scalar_t__ POLICY_CHECK ; 
 int /*<<< orphan*/  ima_appraise_flag (scalar_t__) ; 
 int /*<<< orphan*/  ima_default_rules ; 
 int /*<<< orphan*/  ima_policy_rules ; 
 struct ima_rule_entry* kmemdup (struct ima_rule_entry*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_ima_appraise ; 

__attribute__((used)) static void add_rules(struct ima_rule_entry *entries, int count,
		      enum policy_rule_list policy_rule)
{
	int i = 0;

	for (i = 0; i < count; i++) {
		struct ima_rule_entry *entry;

		if (policy_rule & IMA_DEFAULT_POLICY)
			list_add_tail(&entries[i].list, &ima_default_rules);

		if (policy_rule & IMA_CUSTOM_POLICY) {
			entry = kmemdup(&entries[i], sizeof(*entry),
					GFP_KERNEL);
			if (!entry)
				continue;

			list_add_tail(&entry->list, &ima_policy_rules);
		}
		if (entries[i].action == APPRAISE) {
			temp_ima_appraise |= ima_appraise_flag(entries[i].func);
			if (entries[i].func == POLICY_CHECK)
				temp_ima_appraise |= IMA_APPRAISE_POLICY;
		}
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ima_rule_entry {TYPE_1__* lsm; } ;
struct TYPE_2__ {struct ima_rule_entry* args_p; struct ima_rule_entry* rule; } ;

/* Variables and functions */
 int MAX_LSM_RULES ; 
 int /*<<< orphan*/  kfree (struct ima_rule_entry*) ; 

__attribute__((used)) static void ima_lsm_free_rule(struct ima_rule_entry *entry)
{
	int i;

	for (i = 0; i < MAX_LSM_RULES; i++) {
		kfree(entry->lsm[i].rule);
		kfree(entry->lsm[i].args_p);
	}
	kfree(entry);
}
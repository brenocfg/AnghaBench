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
struct TYPE_2__ {scalar_t__ exe; } ;
struct audit_entry {TYPE_1__ rule; } ;

/* Variables and functions */
#define  AUDIT_ADD_RULE 129 
#define  AUDIT_DEL_RULE 128 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (struct audit_entry*) ; 
 int PTR_ERR (struct audit_entry*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int audit_add_rule (struct audit_entry*) ; 
 struct audit_entry* audit_data_to_entry (void*,size_t) ; 
 int audit_del_rule (struct audit_entry*) ; 
 int /*<<< orphan*/  audit_free_rule (struct audit_entry*) ; 
 int /*<<< orphan*/  audit_log_rule_change (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  audit_remove_mark (scalar_t__) ; 

int audit_rule_change(int type, int seq, void *data, size_t datasz)
{
	int err = 0;
	struct audit_entry *entry;

	switch (type) {
	case AUDIT_ADD_RULE:
		entry = audit_data_to_entry(data, datasz);
		if (IS_ERR(entry))
			return PTR_ERR(entry);
		err = audit_add_rule(entry);
		audit_log_rule_change("add_rule", &entry->rule, !err);
		break;
	case AUDIT_DEL_RULE:
		entry = audit_data_to_entry(data, datasz);
		if (IS_ERR(entry))
			return PTR_ERR(entry);
		err = audit_del_rule(entry);
		audit_log_rule_change("remove_rule", &entry->rule, !err);
		break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	if (err || type == AUDIT_DEL_RULE) {
		if (entry->rule.exe)
			audit_remove_mark(entry->rule.exe);
		audit_free_rule(entry);
	}

	return err;
}
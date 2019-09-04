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
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_INTEGRITY_STATUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int ima_parse_rule (char*,struct ima_rule_entry*) ; 
 int /*<<< orphan*/  ima_temp_rules ; 
 int /*<<< orphan*/  integrity_audit_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*,int,int) ; 
 int /*<<< orphan*/  kfree (struct ima_rule_entry*) ; 
 struct ima_rule_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  strspn (char*,char*) ; 

ssize_t ima_parse_add_rule(char *rule)
{
	static const char op[] = "update_policy";
	char *p;
	struct ima_rule_entry *entry;
	ssize_t result, len;
	int audit_info = 0;

	p = strsep(&rule, "\n");
	len = strlen(p) + 1;
	p += strspn(p, " \t");

	if (*p == '#' || *p == '\0')
		return len;

	entry = kzalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
				    NULL, op, "-ENOMEM", -ENOMEM, audit_info);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&entry->list);

	result = ima_parse_rule(p, entry);
	if (result) {
		kfree(entry);
		integrity_audit_msg(AUDIT_INTEGRITY_STATUS, NULL,
				    NULL, op, "invalid-policy", result,
				    audit_info);
		return result;
	}

	list_add_tail(&entry->list, &ima_temp_rules);

	return len;
}
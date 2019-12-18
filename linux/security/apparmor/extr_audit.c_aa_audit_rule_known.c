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
struct audit_krule {int field_count; struct audit_field* fields; } ;
struct audit_field {int type; } ;

/* Variables and functions */
#define  AUDIT_SUBJ_ROLE 128 

int aa_audit_rule_known(struct audit_krule *rule)
{
	int i;

	for (i = 0; i < rule->field_count; i++) {
		struct audit_field *f = &rule->fields[i];

		switch (f->type) {
		case AUDIT_SUBJ_ROLE:
			return 1;
		}
	}

	return 0;
}
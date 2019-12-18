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
struct audit_field {char* lsm_str; int /*<<< orphan*/  lsm_rule; int /*<<< orphan*/  op; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char*) ; 
 int security_audit_rule_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int audit_dupe_lsm_field(struct audit_field *df,
					   struct audit_field *sf)
{
	int ret = 0;
	char *lsm_str;

	/* our own copy of lsm_str */
	lsm_str = kstrdup(sf->lsm_str, GFP_KERNEL);
	if (unlikely(!lsm_str))
		return -ENOMEM;
	df->lsm_str = lsm_str;

	/* our own (refreshed) copy of lsm_rule */
	ret = security_audit_rule_init(df->type, df->op, df->lsm_str,
				       (void **)&df->lsm_rule);
	/* Keep currently invalid fields around in case they
	 * become valid after a policy reload. */
	if (ret == -EINVAL) {
		pr_warn("audit rule for LSM \'%s\' is invalid\n",
			df->lsm_str);
		ret = 0;
	}

	return ret;
}
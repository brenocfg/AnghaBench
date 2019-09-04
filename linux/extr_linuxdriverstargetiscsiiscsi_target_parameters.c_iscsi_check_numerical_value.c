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
struct iscsi_param {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ IS_TYPERANGE_0_TO_2 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_0_TO_32767 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_0_TO_3600 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_0_TO_65535 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_1_TO_65535 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_2_TO_3600 (struct iscsi_param*) ; 
 scalar_t__ IS_TYPERANGE_512_TO_16777215 (struct iscsi_param*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_check_numerical_value(struct iscsi_param *param, char *value_ptr)
{
	char *tmpptr;
	int value = 0;

	value = simple_strtoul(value_ptr, &tmpptr, 0);

	if (IS_TYPERANGE_0_TO_2(param)) {
		if ((value < 0) || (value > 2)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 2.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_0_TO_3600(param)) {
		if ((value < 0) || (value > 3600)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 3600.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_0_TO_32767(param)) {
		if ((value < 0) || (value > 32767)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 32767.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_0_TO_65535(param)) {
		if ((value < 0) || (value > 65535)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 0 and 65535.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_1_TO_65535(param)) {
		if ((value < 1) || (value > 65535)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 1 and 65535.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_2_TO_3600(param)) {
		if ((value < 2) || (value > 3600)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 2 and 3600.\n", param->name);
			return -1;
		}
		return 0;
	}
	if (IS_TYPERANGE_512_TO_16777215(param)) {
		if ((value < 512) || (value > 16777215)) {
			pr_err("Illegal value for \"%s\", must be"
				" between 512 and 16777215.\n", param->name);
			return -1;
		}
		return 0;
	}

	return 0;
}
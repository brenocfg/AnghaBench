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
 int /*<<< orphan*/  NO ; 
 int /*<<< orphan*/  YES ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_check_boolean_value(struct iscsi_param *param, char *value)
{
	if (strcmp(value, YES) && strcmp(value, NO)) {
		pr_err("Illegal value for \"%s\", must be either"
			" \"%s\" or \"%s\".\n", param->name, YES, NO);
		return -1;
	}

	return 0;
}
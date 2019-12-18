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

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * field_order ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  is_strict_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_hpp_list ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int setup_output_list (int /*<<< orphan*/ *,char*) ; 
 char* strdup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int __setup_output_field(void)
{
	char *str, *strp;
	int ret = -EINVAL;

	if (field_order == NULL)
		return 0;

	strp = str = strdup(field_order);
	if (str == NULL) {
		pr_err("Not enough memory to setup output fields");
		return -ENOMEM;
	}

	if (!is_strict_order(field_order))
		strp++;

	if (!strlen(strp)) {
		pr_err("Invalid --fields key: `+'");
		goto out;
	}

	ret = setup_output_list(&perf_hpp_list, strp);

out:
	free(str);
	return ret;
}
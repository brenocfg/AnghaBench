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
 unsigned int CGRP_ROOT_NS_DELEGATE ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int parse_cgroup_root_flags(char *data, unsigned int *root_flags)
{
	char *token;

	*root_flags = 0;

	if (!data || *data == '\0')
		return 0;

	while ((token = strsep(&data, ",")) != NULL) {
		if (!strcmp(token, "nsdelegate")) {
			*root_flags |= CGRP_ROOT_NS_DELEGATE;
			continue;
		}

		pr_err("cgroup2: unknown option \"%s\"\n", token);
		return -EINVAL;
	}

	return 0;
}
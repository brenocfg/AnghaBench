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
 int /*<<< orphan*/  PERFPROBE_GROUP ; 
 char* basename (char*) ; 
 int e_snprintf (char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  isalnum (char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int convert_exec_to_group(const char *exec, char **result)
{
	char *ptr1, *ptr2, *exec_copy;
	char buf[64];
	int ret;

	exec_copy = strdup(exec);
	if (!exec_copy)
		return -ENOMEM;

	ptr1 = basename(exec_copy);
	if (!ptr1) {
		ret = -EINVAL;
		goto out;
	}

	for (ptr2 = ptr1; *ptr2 != '\0'; ptr2++) {
		if (!isalnum(*ptr2) && *ptr2 != '_') {
			*ptr2 = '\0';
			break;
		}
	}

	ret = e_snprintf(buf, 64, "%s_%s", PERFPROBE_GROUP, ptr1);
	if (ret < 0)
		goto out;

	*result = strdup(buf);
	ret = *result ? 0 : -ENOMEM;

out:
	free(exec_copy);
	return ret;
}
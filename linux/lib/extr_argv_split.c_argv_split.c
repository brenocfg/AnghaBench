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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ KMALLOC_MAX_SIZE ; 
 int count_argc (char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 char* kstrndup (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

char **argv_split(gfp_t gfp, const char *str, int *argcp)
{
	char *argv_str;
	bool was_space;
	char **argv, **argv_ret;
	int argc;

	argv_str = kstrndup(str, KMALLOC_MAX_SIZE - 1, gfp);
	if (!argv_str)
		return NULL;

	argc = count_argc(argv_str);
	argv = kmalloc_array(argc + 2, sizeof(*argv), gfp);
	if (!argv) {
		kfree(argv_str);
		return NULL;
	}

	*argv = argv_str;
	argv_ret = ++argv;
	for (was_space = true; *argv_str; argv_str++) {
		if (isspace(*argv_str)) {
			was_space = true;
			*argv_str = 0;
		} else if (was_space) {
			was_space = false;
			*argv++ = argv_str;
		}
	}
	*argv = NULL;

	if (argcp)
		*argcp = argc;
	return argv_ret;
}
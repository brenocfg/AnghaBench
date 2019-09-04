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
 int /*<<< orphan*/  PATH_MAX ; 
 char* READ_PATH_FMT ; 
 char* WRITE_PATH_FMT ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 char* zalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *make_path(int cpu_num, bool this_is_write_path)
{
	int ret;
	char *buf;

	buf = zalloc(PATH_MAX);
	if (buf == NULL) {
		pr_err("Could not allocate buffer\n");
		goto error;
	}

	if (this_is_write_path)
		/* write(output) path */
		ret = snprintf(buf, PATH_MAX, WRITE_PATH_FMT, cpu_num);
	else
		/* read(input) path */
		ret = snprintf(buf, PATH_MAX, READ_PATH_FMT, cpu_num);

	if (ret <= 0) {
		pr_err("Failed to generate %s path(CPU#%d):%d\n",
			this_is_write_path ? "read" : "write", cpu_num, ret);
		goto error;
	}

	return buf;

error:
	free(buf);
	return NULL;
}
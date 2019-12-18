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
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  READING_POLICY ; 
 int ima_parse_add_rule (char*) ; 
 int kernel_read_file_from_path (char*,void**,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 
 int strlen (char*) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static ssize_t ima_read_policy(char *path)
{
	void *data;
	char *datap;
	loff_t size;
	int rc, pathlen = strlen(path);

	char *p;

	/* remove \n */
	datap = path;
	strsep(&datap, "\n");

	rc = kernel_read_file_from_path(path, &data, &size, 0, READING_POLICY);
	if (rc < 0) {
		pr_err("Unable to open file: %s (%d)", path, rc);
		return rc;
	}

	datap = data;
	while (size > 0 && (p = strsep(&datap, "\n"))) {
		pr_debug("rule: %s\n", p);
		rc = ima_parse_add_rule(p);
		if (rc < 0)
			break;
		size -= rc;
	}

	vfree(data);
	if (rc < 0)
		return rc;
	else if (size)
		return -EINVAL;
	else
		return pathlen;
}
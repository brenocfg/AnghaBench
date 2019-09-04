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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  is_dir (char*) ; 
 scalar_t__ mkdir (char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int make_parent_dir(const char *path)
{
	char tmp[PATH_MAX + 1];
	char *p;

	strncpy(tmp, path, sizeof(tmp));
	tmp[sizeof(tmp) - 1] = 0;

	/* Remove the base name. Just return if nothing is left */
	p = strrchr(tmp, '/');
	if (!p)
		return 0;
	*(p + 1) = 0;

	/* Just in case it is an absolute path */
	p = tmp;
	while (*p == '/')
		p++;

	while ((p = strchr(p, '/'))) {
		*p = 0;

		/* skip if the directory exists */
		if (!is_dir(tmp) && mkdir(tmp, 0755))
			return -1;

		*p = '/';
		while (*p == '/')
			p++;
	}

	return 0;
}
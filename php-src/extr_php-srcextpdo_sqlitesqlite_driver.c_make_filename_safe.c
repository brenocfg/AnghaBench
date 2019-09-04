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
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char const*) ; 
 char* expand_filepath (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 scalar_t__ php_check_open_basedir (char*) ; 

__attribute__((used)) static char *make_filename_safe(const char *filename)
{
	if (*filename && memcmp(filename, ":memory:", sizeof(":memory:"))) {
		char *fullpath = expand_filepath(filename, NULL);

		if (!fullpath) {
			return NULL;
		}

		if (php_check_open_basedir(fullpath)) {
			efree(fullpath);
			return NULL;
		}
		return fullpath;
	}
	return estrdup(filename);
}
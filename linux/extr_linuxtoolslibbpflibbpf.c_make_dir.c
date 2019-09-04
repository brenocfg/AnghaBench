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
typedef  int /*<<< orphan*/  errmsg ;

/* Variables and functions */
 int EEXIST ; 
 int STRERR_BUFSIZE ; 
 int errno ; 
 scalar_t__ mkdir (char const*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,char*) ; 
 char* str_error (int,char*,int) ; 

__attribute__((used)) static int make_dir(const char *path)
{
	char *cp, errmsg[STRERR_BUFSIZE];
	int err = 0;

	if (mkdir(path, 0700) && errno != EEXIST)
		err = -errno;

	if (err) {
		cp = str_error(-err, errmsg, sizeof(errmsg));
		pr_warning("failed to mkdir %s: %s\n", path, cp);
	}
	return err;
}
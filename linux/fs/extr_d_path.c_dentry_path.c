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
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENAMETOOLONG ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (char*) ; 
 char* __dentry_path (struct dentry*,char*,int) ; 
 scalar_t__ d_unlinked (struct dentry*) ; 
 scalar_t__ prepend (char**,int*,char*,int) ; 

char *dentry_path(struct dentry *dentry, char *buf, int buflen)
{
	char *p = NULL;
	char *retval;

	if (d_unlinked(dentry)) {
		p = buf + buflen;
		if (prepend(&p, &buflen, "//deleted", 10) != 0)
			goto Elong;
		buflen++;
	}
	retval = __dentry_path(dentry, buf, buflen);
	if (!IS_ERR(retval) && p)
		*p = '/';	/* restore '/' overriden with '\0' */
	return retval;
Elong:
	return ERR_PTR(-ENAMETOOLONG);
}
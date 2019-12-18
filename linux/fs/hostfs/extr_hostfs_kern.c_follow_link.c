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
 int E2BIG ; 
 int ENOMEM ; 
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PATH_MAX ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int hostfs_do_readlink (char*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *follow_link(char *link)
{
	int len, n;
	char *name, *resolved, *end;

	name = __getname();
	if (!name) {
		n = -ENOMEM;
		goto out_free;
	}

	n = hostfs_do_readlink(link, name, PATH_MAX);
	if (n < 0)
		goto out_free;
	else if (n == PATH_MAX) {
		n = -E2BIG;
		goto out_free;
	}

	if (*name == '/')
		return name;

	end = strrchr(link, '/');
	if (end == NULL)
		return name;

	*(end + 1) = '\0';
	len = strlen(link) + strlen(name) + 1;

	resolved = kmalloc(len, GFP_KERNEL);
	if (resolved == NULL) {
		n = -ENOMEM;
		goto out_free;
	}

	sprintf(resolved, "%s%s", link, name);
	__putname(name);
	kfree(link);
	return resolved;

 out_free:
	__putname(name);
	return ERR_PTR(n);
}
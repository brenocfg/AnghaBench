#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {char* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (char*) ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  __putname (char*) ; 
 char* dentry_path_raw (struct dentry*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *__dentry_name(struct dentry *dentry, char *name)
{
	char *p = dentry_path_raw(dentry, name, PATH_MAX);
	char *root;
	size_t len;

	root = dentry->d_sb->s_fs_info;
	len = strlen(root);
	if (IS_ERR(p)) {
		__putname(name);
		return NULL;
	}

	/*
	 * This function relies on the fact that dentry_path_raw() will place
	 * the path name at the end of the provided buffer.
	 */
	BUG_ON(p + strlen(p) + 1 != name + PATH_MAX);

	strlcpy(name, root, PATH_MAX);
	if (len > p - name) {
		__putname(name);
		return NULL;
	}

	if (p > name + len)
		strcpy(name + len, p);

	return name;
}
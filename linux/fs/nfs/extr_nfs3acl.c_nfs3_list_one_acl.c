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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ IS_ERR_OR_NULL (struct posix_acl*) ; 
 struct posix_acl* get_acl (struct inode*,int) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
nfs3_list_one_acl(struct inode *inode, int type, const char *name, void *data,
		size_t size, ssize_t *result)
{
	struct posix_acl *acl;
	char *p = data + *result;

	acl = get_acl(inode, type);
	if (IS_ERR_OR_NULL(acl))
		return 0;

	posix_acl_release(acl);

	*result += strlen(name);
	*result += 1;
	if (!size)
		return 0;
	if (*result > size)
		return -ERANGE;

	strcpy(p, name);
	return 0;
}
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
struct gfs2_inode {int /*<<< orphan*/  i_eattr; } ;

/* Variables and functions */
 struct posix_acl* ERR_PTR (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 char* gfs2_acl_name (int) ; 
 int gfs2_xattr_acl_get (struct gfs2_inode*,char const*,char**) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct posix_acl* posix_acl_from_xattr (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static struct posix_acl *__gfs2_get_acl(struct inode *inode, int type)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct posix_acl *acl;
	const char *name;
	char *data;
	int len;

	if (!ip->i_eattr)
		return NULL;

	name = gfs2_acl_name(type);
	len = gfs2_xattr_acl_get(ip, name, &data);
	if (len <= 0)
		return ERR_PTR(len);
	acl = posix_acl_from_xattr(&init_user_ns, data, len);
	kfree(data);
	return acl;
}
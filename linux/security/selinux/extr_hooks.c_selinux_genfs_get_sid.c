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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct super_block {TYPE_1__* s_type; } ;
struct dentry {struct super_block* d_sb; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int PTR_ERR (char*) ; 
 int /*<<< orphan*/  SECINITSID_UNLABELED ; 
 int SE_SBPROC ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 char* dentry_path_raw (struct dentry*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int security_genfs_sid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_genfs_get_sid(struct dentry *dentry,
				 u16 tclass,
				 u16 flags,
				 u32 *sid)
{
	int rc;
	struct super_block *sb = dentry->d_sb;
	char *buffer, *path;

	buffer = (char *)__get_free_page(GFP_KERNEL);
	if (!buffer)
		return -ENOMEM;

	path = dentry_path_raw(dentry, buffer, PAGE_SIZE);
	if (IS_ERR(path))
		rc = PTR_ERR(path);
	else {
		if (flags & SE_SBPROC) {
			/* each process gets a /proc/PID/ entry. Strip off the
			 * PID part to get a valid selinux labeling.
			 * e.g. /proc/1/net/rpc/nfs -> /net/rpc/nfs */
			while (path[1] >= '0' && path[1] <= '9') {
				path[1] = '/';
				path++;
			}
		}
		rc = security_genfs_sid(&selinux_state, sb->s_type->name,
					path, tclass, sid);
		if (rc == -ENOENT) {
			/* No match in policy, mark as unlabeled. */
			*sid = SECINITSID_UNLABELED;
			rc = 0;
		}
	}
	free_page((unsigned long)buffer);
	return rc;
}
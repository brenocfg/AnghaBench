#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_flags; struct gfs2_sbd* s_fs_info; } ;
struct path {TYPE_2__* dentry; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_master_dir; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {TYPE_1__* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 struct dentry* ERR_CAST (struct super_block*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_fs_type ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  set_meta_super ; 
 struct super_block* sget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_gfs2_super ; 

__attribute__((used)) static struct dentry *gfs2_mount_meta(struct file_system_type *fs_type,
			int flags, const char *dev_name, void *data)
{
	struct super_block *s;
	struct gfs2_sbd *sdp;
	struct path path;
	int error;

	if (!dev_name || !*dev_name)
		return ERR_PTR(-EINVAL);

	error = kern_path(dev_name, LOOKUP_FOLLOW, &path);
	if (error) {
		pr_warn("path_lookup on %s returned error %d\n",
			dev_name, error);
		return ERR_PTR(error);
	}
	s = sget(&gfs2_fs_type, test_gfs2_super, set_meta_super, flags,
		 path.dentry->d_sb->s_bdev);
	path_put(&path);
	if (IS_ERR(s)) {
		pr_warn("gfs2 mount does not exist\n");
		return ERR_CAST(s);
	}
	if ((flags ^ s->s_flags) & SB_RDONLY) {
		deactivate_locked_super(s);
		return ERR_PTR(-EBUSY);
	}
	sdp = s->s_fs_info;
	return dget(sdp->sd_master_dir);
}
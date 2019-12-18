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
struct fs_context {int sb_flags; int /*<<< orphan*/  root; int /*<<< orphan*/  sget_key; int /*<<< orphan*/ * fs_type; int /*<<< orphan*/ * source; } ;
struct TYPE_4__ {TYPE_1__* d_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int PTR_ERR (struct super_block*) ; 
 int SB_RDONLY ; 
 int /*<<< orphan*/  deactivate_locked_super (struct super_block*) ; 
 int /*<<< orphan*/  dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_fs_type ; 
 int kern_path (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct path*) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  set_meta_super ; 
 struct super_block* sget_fc (struct fs_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_meta_super ; 

__attribute__((used)) static int gfs2_meta_get_tree(struct fs_context *fc)
{
	struct super_block *s;
	struct gfs2_sbd *sdp;
	struct path path;
	int error;

	if (!fc->source || !*fc->source)
		return -EINVAL;

	error = kern_path(fc->source, LOOKUP_FOLLOW, &path);
	if (error) {
		pr_warn("path_lookup on %s returned error %d\n",
		        fc->source, error);
		return error;
	}
	fc->fs_type = &gfs2_fs_type;
	fc->sget_key = path.dentry->d_sb->s_bdev;
	s = sget_fc(fc, test_meta_super, set_meta_super);
	path_put(&path);
	if (IS_ERR(s)) {
		pr_warn("gfs2 mount does not exist\n");
		return PTR_ERR(s);
	}
	if ((fc->sb_flags ^ s->s_flags) & SB_RDONLY) {
		deactivate_locked_super(s);
		return -EBUSY;
	}
	sdp = s->s_fs_info;
	fc->root = dget(sdp->sd_master_dir);
	return 0;
}
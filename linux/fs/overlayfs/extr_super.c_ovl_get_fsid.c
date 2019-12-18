#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_uuid; } ;
struct path {int /*<<< orphan*/  dentry; TYPE_1__* mnt; } ;
struct TYPE_7__ {int index; int nfs_export; } ;
struct ovl_fs {unsigned int numlowerfs; TYPE_4__* lower_fs; TYPE_3__ config; TYPE_2__* upper_mnt; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_8__ {int /*<<< orphan*/  pseudo_dev; struct super_block* sb; } ;
struct TYPE_6__ {struct super_block* mnt_sb; } ;
struct TYPE_5__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 int get_anon_bdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ovl_lower_uuid_ok (struct ovl_fs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ovl_get_fsid(struct ovl_fs *ofs, const struct path *path)
{
	struct super_block *sb = path->mnt->mnt_sb;
	unsigned int i;
	dev_t dev;
	int err;

	/* fsid 0 is reserved for upper fs even with non upper overlay */
	if (ofs->upper_mnt && ofs->upper_mnt->mnt_sb == sb)
		return 0;

	for (i = 0; i < ofs->numlowerfs; i++) {
		if (ofs->lower_fs[i].sb == sb)
			return i + 1;
	}

	if (!ovl_lower_uuid_ok(ofs, &sb->s_uuid)) {
		ofs->config.index = false;
		ofs->config.nfs_export = false;
		pr_warn("overlayfs: %s uuid detected in lower fs '%pd2', falling back to index=off,nfs_export=off.\n",
			uuid_is_null(&sb->s_uuid) ? "null" : "conflicting",
			path->dentry);
	}

	err = get_anon_bdev(&dev);
	if (err) {
		pr_err("overlayfs: failed to get anonymous bdev for lowerpath\n");
		return err;
	}

	ofs->lower_fs[ofs->numlowerfs].sb = sb;
	ofs->lower_fs[ofs->numlowerfs].pseudo_dev = dev;
	ofs->numlowerfs++;

	return ofs->numlowerfs;
}
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
struct super_block {int dummy; } ;
struct ovl_fs {unsigned int numlowerfs; TYPE_1__* lower_fs; TYPE_2__* upper_mnt; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {struct super_block* mnt_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  pseudo_dev; struct super_block* sb; } ;

/* Variables and functions */
 int get_anon_bdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int ovl_get_fsid(struct ovl_fs *ofs, struct super_block *sb)
{
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
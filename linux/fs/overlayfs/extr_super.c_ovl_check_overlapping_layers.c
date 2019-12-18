#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ovl_fs {int numlower; TYPE_2__* lower_layers; int /*<<< orphan*/  workbasedir; TYPE_3__* upper_mnt; } ;
struct TYPE_6__ {int /*<<< orphan*/  mnt_root; } ;
struct TYPE_5__ {TYPE_1__* mnt; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_root; } ;

/* Variables and functions */
 int ovl_check_layer (struct super_block*,struct ovl_fs*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ovl_check_overlapping_layers(struct super_block *sb,
					struct ovl_fs *ofs)
{
	int i, err;

	if (ofs->upper_mnt) {
		err = ovl_check_layer(sb, ofs, ofs->upper_mnt->mnt_root,
				      "upperdir");
		if (err)
			return err;

		/*
		 * Checking workbasedir avoids hitting ovl_is_inuse(parent) of
		 * this instance and covers overlapping work and index dirs,
		 * unless work or index dir have been moved since created inside
		 * workbasedir.  In that case, we already have their traps in
		 * inode cache and we will catch that case on lookup.
		 */
		err = ovl_check_layer(sb, ofs, ofs->workbasedir, "workdir");
		if (err)
			return err;
	}

	for (i = 0; i < ofs->numlower; i++) {
		err = ovl_check_layer(sb, ofs,
				      ofs->lower_layers[i].mnt->mnt_root,
				      "lowerdir");
		if (err)
			return err;
	}

	return 0;
}
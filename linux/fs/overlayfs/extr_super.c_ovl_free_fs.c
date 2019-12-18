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
struct TYPE_3__ {struct ovl_fs* redirect_mode; struct ovl_fs* workdir; struct ovl_fs* upperdir; struct ovl_fs* lowerdir; } ;
struct ovl_fs {unsigned int numlower; unsigned int numlowerfs; scalar_t__ creator_cred; TYPE_1__ config; struct ovl_fs* lower_fs; struct ovl_fs* lower_layers; int /*<<< orphan*/  pseudo_dev; TYPE_2__* mnt; int /*<<< orphan*/  trap; TYPE_2__* upper_mnt; scalar_t__ upperdir_locked; int /*<<< orphan*/  workbasedir; scalar_t__ workdir_locked; int /*<<< orphan*/  workdir; int /*<<< orphan*/  indexdir; int /*<<< orphan*/  upperdir_trap; int /*<<< orphan*/  workdir_trap; int /*<<< orphan*/  indexdir_trap; int /*<<< orphan*/  workbasedir_trap; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_anon_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ovl_fs*) ; 
 int /*<<< orphan*/  mntput (TYPE_2__*) ; 
 int /*<<< orphan*/  ovl_inuse_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cred (scalar_t__) ; 

__attribute__((used)) static void ovl_free_fs(struct ovl_fs *ofs)
{
	unsigned i;

	iput(ofs->workbasedir_trap);
	iput(ofs->indexdir_trap);
	iput(ofs->workdir_trap);
	iput(ofs->upperdir_trap);
	dput(ofs->indexdir);
	dput(ofs->workdir);
	if (ofs->workdir_locked)
		ovl_inuse_unlock(ofs->workbasedir);
	dput(ofs->workbasedir);
	if (ofs->upperdir_locked)
		ovl_inuse_unlock(ofs->upper_mnt->mnt_root);
	mntput(ofs->upper_mnt);
	for (i = 0; i < ofs->numlower; i++) {
		iput(ofs->lower_layers[i].trap);
		mntput(ofs->lower_layers[i].mnt);
	}
	for (i = 0; i < ofs->numlowerfs; i++)
		free_anon_bdev(ofs->lower_fs[i].pseudo_dev);
	kfree(ofs->lower_layers);
	kfree(ofs->lower_fs);

	kfree(ofs->config.lowerdir);
	kfree(ofs->config.upperdir);
	kfree(ofs->config.workdir);
	kfree(ofs->config.redirect_mode);
	if (ofs->creator_cred)
		put_cred(ofs->creator_cred);
	kfree(ofs);
}
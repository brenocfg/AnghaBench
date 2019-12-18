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
struct the_nilfs {int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_sem; } ;
struct super_block {int s_time_gran; int /*<<< orphan*/ * s_root; TYPE_1__* s_bdev; int /*<<< orphan*/  s_bdi; int /*<<< orphan*/  s_max_links; int /*<<< orphan*/ * s_export_op; int /*<<< orphan*/ * s_op; struct the_nilfs* s_fs_info; } ;
struct nilfs_root {int dummy; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  bd_bdi; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NILFS_LINK_MAX ; 
 struct the_nilfs* alloc_nilfs (struct super_block*) ; 
 int /*<<< orphan*/  bdi_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_nilfs (struct the_nilfs*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int init_nilfs (struct the_nilfs*,struct super_block*,char*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int load_nilfs (struct the_nilfs*,struct super_block*) ; 
 int nilfs_attach_checkpoint (struct super_block*,scalar_t__,int,struct nilfs_root**) ; 
 int nilfs_attach_log_writer (struct super_block*,struct nilfs_root*) ; 
 int /*<<< orphan*/  nilfs_detach_log_writer (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_export_ops ; 
 int nilfs_get_root_dentry (struct super_block*,struct nilfs_root*,int /*<<< orphan*/ **) ; 
 scalar_t__ nilfs_last_cno (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,int,unsigned long long) ; 
 int /*<<< orphan*/  nilfs_put_root (struct nilfs_root*) ; 
 int /*<<< orphan*/  nilfs_setup_super (struct super_block*,int) ; 
 int /*<<< orphan*/  nilfs_sops ; 
 int /*<<< orphan*/  sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nilfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct the_nilfs *nilfs;
	struct nilfs_root *fsroot;
	__u64 cno;
	int err;

	nilfs = alloc_nilfs(sb);
	if (!nilfs)
		return -ENOMEM;

	sb->s_fs_info = nilfs;

	err = init_nilfs(nilfs, sb, (char *)data);
	if (err)
		goto failed_nilfs;

	sb->s_op = &nilfs_sops;
	sb->s_export_op = &nilfs_export_ops;
	sb->s_root = NULL;
	sb->s_time_gran = 1;
	sb->s_max_links = NILFS_LINK_MAX;

	sb->s_bdi = bdi_get(sb->s_bdev->bd_bdi);

	err = load_nilfs(nilfs, sb);
	if (err)
		goto failed_nilfs;

	cno = nilfs_last_cno(nilfs);
	err = nilfs_attach_checkpoint(sb, cno, true, &fsroot);
	if (err) {
		nilfs_msg(sb, KERN_ERR,
			  "error %d while loading last checkpoint (checkpoint number=%llu)",
			  err, (unsigned long long)cno);
		goto failed_unload;
	}

	if (!sb_rdonly(sb)) {
		err = nilfs_attach_log_writer(sb, fsroot);
		if (err)
			goto failed_checkpoint;
	}

	err = nilfs_get_root_dentry(sb, fsroot, &sb->s_root);
	if (err)
		goto failed_segctor;

	nilfs_put_root(fsroot);

	if (!sb_rdonly(sb)) {
		down_write(&nilfs->ns_sem);
		nilfs_setup_super(sb, true);
		up_write(&nilfs->ns_sem);
	}

	return 0;

 failed_segctor:
	nilfs_detach_log_writer(sb);

 failed_checkpoint:
	nilfs_put_root(fsroot);

 failed_unload:
	iput(nilfs->ns_sufile);
	iput(nilfs->ns_cpfile);
	iput(nilfs->ns_dat);

 failed_nilfs:
	destroy_nilfs(nilfs);
	return err;
}
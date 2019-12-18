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
struct super_block {int s_blocksize; int s_blocksize_bits; int s_time_gran; struct autofs_sb_info* s_fs_info; struct dentry* s_root; int /*<<< orphan*/ * s_d_op; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; } ;
struct inode {int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; } ;
struct file {int dummy; } ;
struct dentry {struct autofs_info* d_fsdata; } ;
struct autofs_sb_info {int pipefd; scalar_t__ version; scalar_t__ min_proto; scalar_t__ max_proto; int /*<<< orphan*/ * oz_pgrp; int /*<<< orphan*/  flags; struct file* pipe; int /*<<< orphan*/  type; scalar_t__ sub_version; int /*<<< orphan*/  expiring_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  lookup_lock; int /*<<< orphan*/ * queues; int /*<<< orphan*/  fs_lock; int /*<<< orphan*/  pipe_mutex; int /*<<< orphan*/  wq_mutex; struct super_block* sb; scalar_t__ exp_timeout; int /*<<< orphan*/  magic; } ;
struct autofs_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ AUTOFS_MAX_PROTO_VERSION ; 
 scalar_t__ AUTOFS_MIN_PROTO_VERSION ; 
 scalar_t__ AUTOFS_PROTO_SUBVERSION ; 
 int /*<<< orphan*/  AUTOFS_SBI_CATATONIC ; 
 int /*<<< orphan*/  AUTOFS_SBI_MAGIC ; 
 int /*<<< orphan*/  AUTOFS_SUPER_MAGIC ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  __managed_dentry_set_managed (struct dentry*) ; 
 int /*<<< orphan*/  autofs_dentry_operations ; 
 int /*<<< orphan*/  autofs_dir_inode_operations ; 
 int /*<<< orphan*/  autofs_free_ino (struct autofs_info*) ; 
 struct inode* autofs_get_inode (struct super_block*,int) ; 
 struct autofs_info* autofs_new_ino (struct autofs_sb_info*) ; 
 int autofs_prepare_pipe (struct file*) ; 
 int /*<<< orphan*/  autofs_root_operations ; 
 int /*<<< orphan*/  autofs_sops ; 
 scalar_t__ autofs_type_trigger (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 struct dentry* d_make_root (struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/ * find_get_pid (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 int /*<<< orphan*/ * get_task_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct autofs_sb_info*) ; 
 struct autofs_sb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_options (void*,struct inode*,int*,int*,struct autofs_sb_info*) ; 
 int /*<<< orphan*/  pid_nr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_autofs_type_indirect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int autofs_fill_super(struct super_block *s, void *data, int silent)
{
	struct inode *root_inode;
	struct dentry *root;
	struct file *pipe;
	struct autofs_sb_info *sbi;
	struct autofs_info *ino;
	int pgrp = 0;
	bool pgrp_set = false;
	int ret = -EINVAL;

	sbi = kzalloc(sizeof(*sbi), GFP_KERNEL);
	if (!sbi)
		return -ENOMEM;
	pr_debug("starting up, sbi = %p\n", sbi);

	s->s_fs_info = sbi;
	sbi->magic = AUTOFS_SBI_MAGIC;
	sbi->pipefd = -1;
	sbi->pipe = NULL;
	sbi->exp_timeout = 0;
	sbi->oz_pgrp = NULL;
	sbi->sb = s;
	sbi->version = 0;
	sbi->sub_version = 0;
	sbi->flags = AUTOFS_SBI_CATATONIC;
	set_autofs_type_indirect(&sbi->type);
	sbi->min_proto = 0;
	sbi->max_proto = 0;
	mutex_init(&sbi->wq_mutex);
	mutex_init(&sbi->pipe_mutex);
	spin_lock_init(&sbi->fs_lock);
	sbi->queues = NULL;
	spin_lock_init(&sbi->lookup_lock);
	INIT_LIST_HEAD(&sbi->active_list);
	INIT_LIST_HEAD(&sbi->expiring_list);
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = AUTOFS_SUPER_MAGIC;
	s->s_op = &autofs_sops;
	s->s_d_op = &autofs_dentry_operations;
	s->s_time_gran = 1;

	/*
	 * Get the root inode and dentry, but defer checking for errors.
	 */
	ino = autofs_new_ino(sbi);
	if (!ino) {
		ret = -ENOMEM;
		goto fail_free;
	}
	root_inode = autofs_get_inode(s, S_IFDIR | 0755);
	root = d_make_root(root_inode);
	if (!root) {
		ret = -ENOMEM;
		goto fail_ino;
	}
	pipe = NULL;

	root->d_fsdata = ino;

	/* Can this call block? */
	if (parse_options(data, root_inode, &pgrp, &pgrp_set, sbi)) {
		pr_err("called with bogus options\n");
		goto fail_dput;
	}

	/* Test versions first */
	if (sbi->max_proto < AUTOFS_MIN_PROTO_VERSION ||
	    sbi->min_proto > AUTOFS_MAX_PROTO_VERSION) {
		pr_err("kernel does not match daemon version "
		       "daemon (%d, %d) kernel (%d, %d)\n",
		       sbi->min_proto, sbi->max_proto,
		       AUTOFS_MIN_PROTO_VERSION, AUTOFS_MAX_PROTO_VERSION);
		goto fail_dput;
	}

	/* Establish highest kernel protocol version */
	if (sbi->max_proto > AUTOFS_MAX_PROTO_VERSION)
		sbi->version = AUTOFS_MAX_PROTO_VERSION;
	else
		sbi->version = sbi->max_proto;
	sbi->sub_version = AUTOFS_PROTO_SUBVERSION;

	if (pgrp_set) {
		sbi->oz_pgrp = find_get_pid(pgrp);
		if (!sbi->oz_pgrp) {
			pr_err("could not find process group %d\n",
				pgrp);
			goto fail_dput;
		}
	} else {
		sbi->oz_pgrp = get_task_pid(current, PIDTYPE_PGID);
	}

	if (autofs_type_trigger(sbi->type))
		__managed_dentry_set_managed(root);

	root_inode->i_fop = &autofs_root_operations;
	root_inode->i_op = &autofs_dir_inode_operations;

	pr_debug("pipe fd = %d, pgrp = %u\n",
		 sbi->pipefd, pid_nr(sbi->oz_pgrp));
	pipe = fget(sbi->pipefd);

	if (!pipe) {
		pr_err("could not open pipe file descriptor\n");
		goto fail_put_pid;
	}
	ret = autofs_prepare_pipe(pipe);
	if (ret < 0)
		goto fail_fput;
	sbi->pipe = pipe;
	sbi->flags &= ~AUTOFS_SBI_CATATONIC;

	/*
	 * Success! Install the root dentry now to indicate completion.
	 */
	s->s_root = root;
	return 0;

	/*
	 * Failure ... clean up.
	 */
fail_fput:
	pr_err("pipe file descriptor does not contain proper ops\n");
	fput(pipe);
fail_put_pid:
	put_pid(sbi->oz_pgrp);
fail_dput:
	dput(root);
	goto fail_free;
fail_ino:
	autofs_free_ino(ino);
fail_free:
	kfree(sbi);
	s->s_fs_info = NULL;
	return ret;
}
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
struct super_block {int s_iflags; int s_flags; int s_blocksize; int s_blocksize_bits; int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_stack_depth; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_fs_info; } ;
struct pid_namespace {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FILESYSTEM_MAX_STACK_DEPTH ; 
 int /*<<< orphan*/  PROC_SUPER_MAGIC ; 
 int SB_I_NODEV ; 
 int SB_I_NOEXEC ; 
 int SB_I_USERNS_VISIBLE ; 
 int SB_NODIRATIME ; 
 int SB_NOEXEC ; 
 int SB_NOSUID ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 struct pid_namespace* get_pid_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pde_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct inode* proc_get_inode (struct super_block*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_parse_options (void*,struct pid_namespace*) ; 
 int /*<<< orphan*/  proc_root ; 
 int proc_setup_self (struct super_block*) ; 
 int proc_setup_thread_self (struct super_block*) ; 
 int /*<<< orphan*/  proc_sops ; 

int proc_fill_super(struct super_block *s, void *data, int silent)
{
	struct pid_namespace *ns = get_pid_ns(s->s_fs_info);
	struct inode *root_inode;
	int ret;

	if (!proc_parse_options(data, ns))
		return -EINVAL;

	/* User space would break if executables or devices appear on proc */
	s->s_iflags |= SB_I_USERNS_VISIBLE | SB_I_NOEXEC | SB_I_NODEV;
	s->s_flags |= SB_NODIRATIME | SB_NOSUID | SB_NOEXEC;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = PROC_SUPER_MAGIC;
	s->s_op = &proc_sops;
	s->s_time_gran = 1;

	/*
	 * procfs isn't actually a stacking filesystem; however, there is
	 * too much magic going on inside it to permit stacking things on
	 * top of it
	 */
	s->s_stack_depth = FILESYSTEM_MAX_STACK_DEPTH;
	
	pde_get(&proc_root);
	root_inode = proc_get_inode(s, &proc_root);
	if (!root_inode) {
		pr_err("proc_fill_super: get root inode failed\n");
		return -ENOMEM;
	}

	s->s_root = d_make_root(root_inode);
	if (!s->s_root) {
		pr_err("proc_fill_super: allocate dentry failed\n");
		return -ENOMEM;
	}

	ret = proc_setup_self(s);
	if (ret) {
		return ret;
	}
	return proc_setup_thread_self(s);
}
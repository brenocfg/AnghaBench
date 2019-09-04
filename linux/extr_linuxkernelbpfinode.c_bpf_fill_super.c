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
struct tree_descr {char* member_0; } ;
struct super_block {TYPE_1__* s_root; int /*<<< orphan*/ * s_op; } ;
struct inode {int i_mode; int /*<<< orphan*/ * i_op; } ;
struct bpf_mount_opts {int mode; } ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_FS_MAGIC ; 
 int S_IALLUGO ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  bpf_dir_iops ; 
 int bpf_parse_options (void*,struct bpf_mount_opts*) ; 
 int /*<<< orphan*/  bpf_super_ops ; 
 int simple_fill_super (struct super_block*,int /*<<< orphan*/ ,struct tree_descr const*) ; 

__attribute__((used)) static int bpf_fill_super(struct super_block *sb, void *data, int silent)
{
	static const struct tree_descr bpf_rfiles[] = { { "" } };
	struct bpf_mount_opts opts;
	struct inode *inode;
	int ret;

	ret = bpf_parse_options(data, &opts);
	if (ret)
		return ret;

	ret = simple_fill_super(sb, BPF_FS_MAGIC, bpf_rfiles);
	if (ret)
		return ret;

	sb->s_op = &bpf_super_ops;

	inode = sb->s_root->d_inode;
	inode->i_op = &bpf_dir_iops;
	inode->i_mode &= ~S_IALLUGO;
	inode->i_mode |= S_ISVTX | opts.mode;

	return 0;
}
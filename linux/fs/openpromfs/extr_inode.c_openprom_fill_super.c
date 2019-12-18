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
struct super_block {int s_blocksize; int s_blocksize_bits; int s_time_gran; int /*<<< orphan*/  s_root; int /*<<< orphan*/ * s_op; int /*<<< orphan*/  s_magic; int /*<<< orphan*/  s_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;
struct op_inode_info {TYPE_1__ u; int /*<<< orphan*/  type; } ;
struct inode {int dummy; } ;
struct fs_context {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  OPENPROM_ROOT_INO ; 
 int /*<<< orphan*/  OPENPROM_SUPER_MAGIC ; 
 struct op_inode_info* OP_I (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  SB_NOATIME ; 
 int /*<<< orphan*/  d_make_root (struct inode*) ; 
 int /*<<< orphan*/  of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  op_inode_node ; 
 struct inode* openprom_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  openprom_sops ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int openprom_fill_super(struct super_block *s, struct fs_context *fc)
{
	struct inode *root_inode;
	struct op_inode_info *oi;
	int ret;

	s->s_flags |= SB_NOATIME;
	s->s_blocksize = 1024;
	s->s_blocksize_bits = 10;
	s->s_magic = OPENPROM_SUPER_MAGIC;
	s->s_op = &openprom_sops;
	s->s_time_gran = 1;
	root_inode = openprom_iget(s, OPENPROM_ROOT_INO);
	if (IS_ERR(root_inode)) {
		ret = PTR_ERR(root_inode);
		goto out_no_root;
	}

	oi = OP_I(root_inode);
	oi->type = op_inode_node;
	oi->u.node = of_find_node_by_path("/");

	s->s_root = d_make_root(root_inode);
	if (!s->s_root)
		goto out_no_root_dentry;
	return 0;

out_no_root_dentry:
	ret = -ENOMEM;
out_no_root:
	printk("openprom_fill_super: get root inode failed\n");
	return ret;
}
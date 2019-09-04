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
struct the_nilfs {int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_inode_size; int /*<<< orphan*/  ns_segctor_sem; } ;
struct super_block {struct the_nilfs* s_fs_info; } ;
struct nilfs_root {int /*<<< orphan*/  blocks_count; int /*<<< orphan*/  inodes_count; scalar_t__ ifile; } ;
struct nilfs_checkpoint {int /*<<< orphan*/  cp_blocks_count; int /*<<< orphan*/  cp_inodes_count; int /*<<< orphan*/  cp_ifile_inode; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ __u64 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ NILFS_CPTREE_CURRENT_CNO ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int nilfs_cpfile_get_checkpoint (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct nilfs_checkpoint**,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_cpfile_put_checkpoint (int /*<<< orphan*/ ,scalar_t__,struct buffer_head*) ; 
 struct nilfs_root* nilfs_find_or_create_root (struct the_nilfs*,scalar_t__) ; 
 int nilfs_ifile_read (struct super_block*,struct nilfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  nilfs_put_root (struct nilfs_root*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_attach_checkpoint(struct super_block *sb, __u64 cno, int curr_mnt,
			    struct nilfs_root **rootp)
{
	struct the_nilfs *nilfs = sb->s_fs_info;
	struct nilfs_root *root;
	struct nilfs_checkpoint *raw_cp;
	struct buffer_head *bh_cp;
	int err = -ENOMEM;

	root = nilfs_find_or_create_root(
		nilfs, curr_mnt ? NILFS_CPTREE_CURRENT_CNO : cno);
	if (!root)
		return err;

	if (root->ifile)
		goto reuse; /* already attached checkpoint */

	down_read(&nilfs->ns_segctor_sem);
	err = nilfs_cpfile_get_checkpoint(nilfs->ns_cpfile, cno, 0, &raw_cp,
					  &bh_cp);
	up_read(&nilfs->ns_segctor_sem);
	if (unlikely(err)) {
		if (err == -ENOENT || err == -EINVAL) {
			nilfs_msg(sb, KERN_ERR,
				  "Invalid checkpoint (checkpoint number=%llu)",
				  (unsigned long long)cno);
			err = -EINVAL;
		}
		goto failed;
	}

	err = nilfs_ifile_read(sb, root, nilfs->ns_inode_size,
			       &raw_cp->cp_ifile_inode, &root->ifile);
	if (err)
		goto failed_bh;

	atomic64_set(&root->inodes_count,
			le64_to_cpu(raw_cp->cp_inodes_count));
	atomic64_set(&root->blocks_count,
			le64_to_cpu(raw_cp->cp_blocks_count));

	nilfs_cpfile_put_checkpoint(nilfs->ns_cpfile, cno, bh_cp);

 reuse:
	*rootp = root;
	return 0;

 failed_bh:
	nilfs_cpfile_put_checkpoint(nilfs->ns_cpfile, cno, bh_cp);
 failed:
	nilfs_put_root(root);

	return err;
}
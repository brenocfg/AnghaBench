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
struct super_block {size_t s_blocksize; } ;
struct nilfs_sufile_info {scalar_t__ allocmin; scalar_t__ allocmax; int /*<<< orphan*/  ncleansegs; } ;
struct nilfs_sufile_header {int /*<<< orphan*/  sh_ncleansegs; } ;
struct nilfs_inode {int dummy; } ;
struct inode {int i_state; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int I_NEW ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NILFS_MDT_GFP ; 
 size_t NILFS_MIN_SEGMENT_USAGE_SIZE ; 
 int /*<<< orphan*/  NILFS_SUFILE_INO ; 
 struct nilfs_sufile_info* NILFS_SUI (struct inode*) ; 
 int bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct inode* nilfs_iget_locked (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_mdt_init (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_mdt_set_entry_size (struct inode*,size_t,int) ; 
 int /*<<< orphan*/  nilfs_msg (struct super_block*,int /*<<< orphan*/ ,char*,size_t) ; 
 int nilfs_read_inode_common (struct inode*,struct nilfs_inode*) ; 
 int nilfs_sufile_get_header_block (struct inode*,struct buffer_head**) ; 
 scalar_t__ nilfs_sufile_get_nsegments (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

int nilfs_sufile_read(struct super_block *sb, size_t susize,
		      struct nilfs_inode *raw_inode, struct inode **inodep)
{
	struct inode *sufile;
	struct nilfs_sufile_info *sui;
	struct buffer_head *header_bh;
	struct nilfs_sufile_header *header;
	void *kaddr;
	int err;

	if (susize > sb->s_blocksize) {
		nilfs_msg(sb, KERN_ERR,
			  "too large segment usage size: %zu bytes", susize);
		return -EINVAL;
	} else if (susize < NILFS_MIN_SEGMENT_USAGE_SIZE) {
		nilfs_msg(sb, KERN_ERR,
			  "too small segment usage size: %zu bytes", susize);
		return -EINVAL;
	}

	sufile = nilfs_iget_locked(sb, NULL, NILFS_SUFILE_INO);
	if (unlikely(!sufile))
		return -ENOMEM;
	if (!(sufile->i_state & I_NEW))
		goto out;

	err = nilfs_mdt_init(sufile, NILFS_MDT_GFP, sizeof(*sui));
	if (err)
		goto failed;

	nilfs_mdt_set_entry_size(sufile, susize,
				 sizeof(struct nilfs_sufile_header));

	err = nilfs_read_inode_common(sufile, raw_inode);
	if (err)
		goto failed;

	err = nilfs_sufile_get_header_block(sufile, &header_bh);
	if (err)
		goto failed;

	sui = NILFS_SUI(sufile);
	kaddr = kmap_atomic(header_bh->b_page);
	header = kaddr + bh_offset(header_bh);
	sui->ncleansegs = le64_to_cpu(header->sh_ncleansegs);
	kunmap_atomic(kaddr);
	brelse(header_bh);

	sui->allocmax = nilfs_sufile_get_nsegments(sufile) - 1;
	sui->allocmin = 0;

	unlock_new_inode(sufile);
 out:
	*inodep = sufile;
	return 0;
 failed:
	iget_failed(sufile);
	return err;
}
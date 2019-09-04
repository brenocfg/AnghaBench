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
struct nilfs_cpfile_header {int /*<<< orphan*/  ch_ncheckpoints; } ;
struct nilfs_checkpoint {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int __u64 ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 void* kmap (int /*<<< orphan*/ ) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le64_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  nilfs_checkpoint_clear_invalid (struct nilfs_checkpoint*) ; 
 scalar_t__ nilfs_checkpoint_invalid (struct nilfs_checkpoint*) ; 
 int /*<<< orphan*/  nilfs_cpfile_block_add_valid_checkpoints (struct inode*,struct buffer_head*,void*,int) ; 
 struct nilfs_checkpoint* nilfs_cpfile_block_get_checkpoint (struct inode*,int,struct buffer_head*,void*) ; 
 struct nilfs_cpfile_header* nilfs_cpfile_block_get_header (struct inode*,struct buffer_head*,void*) ; 
 int nilfs_cpfile_get_checkpoint_block (struct inode*,int,int,struct buffer_head**) ; 
 int nilfs_cpfile_get_header_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_cpfile_is_in_first (struct inode*,int) ; 
 int nilfs_mdt_cno (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mdt_mark_dirty (struct inode*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int nilfs_cpfile_get_checkpoint(struct inode *cpfile,
				__u64 cno,
				int create,
				struct nilfs_checkpoint **cpp,
				struct buffer_head **bhp)
{
	struct buffer_head *header_bh, *cp_bh;
	struct nilfs_cpfile_header *header;
	struct nilfs_checkpoint *cp;
	void *kaddr;
	int ret;

	if (unlikely(cno < 1 || cno > nilfs_mdt_cno(cpfile) ||
		     (cno < nilfs_mdt_cno(cpfile) && create)))
		return -EINVAL;

	down_write(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_header_block(cpfile, &header_bh);
	if (ret < 0)
		goto out_sem;
	ret = nilfs_cpfile_get_checkpoint_block(cpfile, cno, create, &cp_bh);
	if (ret < 0)
		goto out_header;
	kaddr = kmap(cp_bh->b_page);
	cp = nilfs_cpfile_block_get_checkpoint(cpfile, cno, cp_bh, kaddr);
	if (nilfs_checkpoint_invalid(cp)) {
		if (!create) {
			kunmap(cp_bh->b_page);
			brelse(cp_bh);
			ret = -ENOENT;
			goto out_header;
		}
		/* a newly-created checkpoint */
		nilfs_checkpoint_clear_invalid(cp);
		if (!nilfs_cpfile_is_in_first(cpfile, cno))
			nilfs_cpfile_block_add_valid_checkpoints(cpfile, cp_bh,
								 kaddr, 1);
		mark_buffer_dirty(cp_bh);

		kaddr = kmap_atomic(header_bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, header_bh,
						       kaddr);
		le64_add_cpu(&header->ch_ncheckpoints, 1);
		kunmap_atomic(kaddr);
		mark_buffer_dirty(header_bh);
		nilfs_mdt_mark_dirty(cpfile);
	}

	if (cpp != NULL)
		*cpp = cp;
	*bhp = cp_bh;

 out_header:
	brelse(header_bh);

 out_sem:
	up_write(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}
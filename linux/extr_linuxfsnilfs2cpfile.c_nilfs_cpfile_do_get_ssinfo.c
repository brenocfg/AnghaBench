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
struct nilfs_cpinfo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ssl_next; } ;
struct nilfs_cpfile_header {TYPE_1__ ch_snapshot_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssl_next; } ;
struct nilfs_checkpoint {TYPE_2__ cp_snapshot_list; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  __u64 ;
struct TYPE_6__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 int ENOENT ; 
 TYPE_3__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_checkpoint_invalid (struct nilfs_checkpoint*) ; 
 int /*<<< orphan*/  nilfs_checkpoint_snapshot (struct nilfs_checkpoint*) ; 
 struct nilfs_checkpoint* nilfs_cpfile_block_get_checkpoint (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,void*) ; 
 struct nilfs_cpfile_header* nilfs_cpfile_block_get_header (struct inode*,struct buffer_head*,void*) ; 
 int /*<<< orphan*/  nilfs_cpfile_checkpoint_to_cpinfo (struct inode*,struct nilfs_checkpoint*,struct nilfs_cpinfo*) ; 
 unsigned long nilfs_cpfile_get_blkoff (struct inode*,int /*<<< orphan*/ ) ; 
 int nilfs_cpfile_get_checkpoint_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int nilfs_cpfile_get_header_block (struct inode*,struct buffer_head**) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t nilfs_cpfile_do_get_ssinfo(struct inode *cpfile, __u64 *cnop,
					  void *buf, unsigned int cisz,
					  size_t nci)
{
	struct buffer_head *bh;
	struct nilfs_cpfile_header *header;
	struct nilfs_checkpoint *cp;
	struct nilfs_cpinfo *ci = buf;
	__u64 curr = *cnop, next;
	unsigned long curr_blkoff, next_blkoff;
	void *kaddr;
	int n = 0, ret;

	down_read(&NILFS_MDT(cpfile)->mi_sem);

	if (curr == 0) {
		ret = nilfs_cpfile_get_header_block(cpfile, &bh);
		if (ret < 0)
			goto out;
		kaddr = kmap_atomic(bh->b_page);
		header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
		curr = le64_to_cpu(header->ch_snapshot_list.ssl_next);
		kunmap_atomic(kaddr);
		brelse(bh);
		if (curr == 0) {
			ret = 0;
			goto out;
		}
	} else if (unlikely(curr == ~(__u64)0)) {
		ret = 0;
		goto out;
	}

	curr_blkoff = nilfs_cpfile_get_blkoff(cpfile, curr);
	ret = nilfs_cpfile_get_checkpoint_block(cpfile, curr, 0, &bh);
	if (unlikely(ret < 0)) {
		if (ret == -ENOENT)
			ret = 0; /* No snapshots (started from a hole block) */
		goto out;
	}
	kaddr = kmap_atomic(bh->b_page);
	while (n < nci) {
		cp = nilfs_cpfile_block_get_checkpoint(cpfile, curr, bh, kaddr);
		curr = ~(__u64)0; /* Terminator */
		if (unlikely(nilfs_checkpoint_invalid(cp) ||
			     !nilfs_checkpoint_snapshot(cp)))
			break;
		nilfs_cpfile_checkpoint_to_cpinfo(cpfile, cp, ci);
		ci = (void *)ci + cisz;
		n++;
		next = le64_to_cpu(cp->cp_snapshot_list.ssl_next);
		if (next == 0)
			break; /* reach end of the snapshot list */

		next_blkoff = nilfs_cpfile_get_blkoff(cpfile, next);
		if (curr_blkoff != next_blkoff) {
			kunmap_atomic(kaddr);
			brelse(bh);
			ret = nilfs_cpfile_get_checkpoint_block(cpfile, next,
								0, &bh);
			if (unlikely(ret < 0)) {
				WARN_ON(ret == -ENOENT);
				goto out;
			}
			kaddr = kmap_atomic(bh->b_page);
		}
		curr = next;
		curr_blkoff = next_blkoff;
	}
	kunmap_atomic(kaddr);
	brelse(bh);
	*cnop = curr;
	ret = n;

 out:
	up_read(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}
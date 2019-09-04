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
struct nilfs_cpstat {void* cs_nsss; void* cs_ncps; int /*<<< orphan*/  cs_cno; } ;
struct nilfs_cpfile_header {int /*<<< orphan*/  ch_nsnapshots; int /*<<< orphan*/  ch_ncheckpoints; } ;
struct inode {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_page; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 void* kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct nilfs_cpfile_header* nilfs_cpfile_block_get_header (struct inode*,struct buffer_head*,void*) ; 
 int nilfs_cpfile_get_header_block (struct inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  nilfs_mdt_cno (struct inode*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int nilfs_cpfile_get_stat(struct inode *cpfile, struct nilfs_cpstat *cpstat)
{
	struct buffer_head *bh;
	struct nilfs_cpfile_header *header;
	void *kaddr;
	int ret;

	down_read(&NILFS_MDT(cpfile)->mi_sem);

	ret = nilfs_cpfile_get_header_block(cpfile, &bh);
	if (ret < 0)
		goto out_sem;
	kaddr = kmap_atomic(bh->b_page);
	header = nilfs_cpfile_block_get_header(cpfile, bh, kaddr);
	cpstat->cs_cno = nilfs_mdt_cno(cpfile);
	cpstat->cs_ncps = le64_to_cpu(header->ch_ncheckpoints);
	cpstat->cs_nsss = le64_to_cpu(header->ch_nsnapshots);
	kunmap_atomic(kaddr);
	brelse(bh);

 out_sem:
	up_read(&NILFS_MDT(cpfile)->mi_sem);
	return ret;
}
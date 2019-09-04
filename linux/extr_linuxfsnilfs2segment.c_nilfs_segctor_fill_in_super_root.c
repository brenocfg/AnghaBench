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
struct the_nilfs {unsigned int ns_inode_size; scalar_t__ ns_blocksize; int /*<<< orphan*/  ns_sufile; int /*<<< orphan*/  ns_cpfile; int /*<<< orphan*/  ns_dat; int /*<<< orphan*/  ns_nongc_ctime; } ;
struct nilfs_super_root {scalar_t__ sr_flags; int /*<<< orphan*/  sr_nongc_ctime; int /*<<< orphan*/  sr_bytes; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_seg_ctime; int /*<<< orphan*/  sc_segbufs; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_2__ {struct buffer_head* sb_super_root; } ;

/* Variables and functions */
 TYPE_1__* NILFS_LAST_SEGBUF (int /*<<< orphan*/ *) ; 
 unsigned int NILFS_SR_BYTES (unsigned int) ; 
 int NILFS_SR_CPFILE_OFFSET (unsigned int) ; 
 int NILFS_SR_DAT_OFFSET (unsigned int) ; 
 int NILFS_SR_SUFILE_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le16 (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nilfs_doing_gc () ; 
 int /*<<< orphan*/  nilfs_write_inode_common (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void nilfs_segctor_fill_in_super_root(struct nilfs_sc_info *sci,
					     struct the_nilfs *nilfs)
{
	struct buffer_head *bh_sr;
	struct nilfs_super_root *raw_sr;
	unsigned int isz, srsz;

	bh_sr = NILFS_LAST_SEGBUF(&sci->sc_segbufs)->sb_super_root;
	raw_sr = (struct nilfs_super_root *)bh_sr->b_data;
	isz = nilfs->ns_inode_size;
	srsz = NILFS_SR_BYTES(isz);

	raw_sr->sr_bytes = cpu_to_le16(srsz);
	raw_sr->sr_nongc_ctime
		= cpu_to_le64(nilfs_doing_gc() ?
			      nilfs->ns_nongc_ctime : sci->sc_seg_ctime);
	raw_sr->sr_flags = 0;

	nilfs_write_inode_common(nilfs->ns_dat, (void *)raw_sr +
				 NILFS_SR_DAT_OFFSET(isz), 1);
	nilfs_write_inode_common(nilfs->ns_cpfile, (void *)raw_sr +
				 NILFS_SR_CPFILE_OFFSET(isz), 1);
	nilfs_write_inode_common(nilfs->ns_sufile, (void *)raw_sr +
				 NILFS_SR_SUFILE_OFFSET(isz), 1);
	memset((void *)raw_sr + srsz, 0, nilfs->ns_blocksize - srsz);
}
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
struct f2fs_summary {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int /*<<< orphan*/  io_type; int /*<<< orphan*/  new_blkaddr; int /*<<< orphan*/  version; struct f2fs_sb_info* sbi; } ;
struct dnode_of_data {scalar_t__ data_blkaddr; int /*<<< orphan*/  ofs_in_node; int /*<<< orphan*/  nid; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 scalar_t__ NULL_ADDR ; 
 int /*<<< orphan*/  do_write_page (struct f2fs_summary*,struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_update_data_blkaddr (struct dnode_of_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_summary (struct f2fs_summary*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void f2fs_outplace_write_data(struct dnode_of_data *dn,
					struct f2fs_io_info *fio)
{
	struct f2fs_sb_info *sbi = fio->sbi;
	struct f2fs_summary sum;

	f2fs_bug_on(sbi, dn->data_blkaddr == NULL_ADDR);
	set_summary(&sum, dn->nid, dn->ofs_in_node, fio->version);
	do_write_page(&sum, fio);
	f2fs_update_data_blkaddr(dn, fio->new_blkaddr);

	f2fs_update_iostat(sbi, fio->io_type, F2FS_BLKSIZE);
}
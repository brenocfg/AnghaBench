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
struct f2fs_io_info {int /*<<< orphan*/  io_type; int /*<<< orphan*/  sbi; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 int /*<<< orphan*/  do_write_page (struct f2fs_summary*,struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_update_iostat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_summary (struct f2fs_summary*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void f2fs_do_write_node_page(unsigned int nid, struct f2fs_io_info *fio)
{
	struct f2fs_summary sum;

	set_summary(&sum, nid, 0, 0);
	do_write_page(&sum, fio);

	f2fs_update_iostat(fio->sbi, fio->io_type, F2FS_BLKSIZE);
}
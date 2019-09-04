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
struct inode {int dummy; } ;
struct f2fs_sb_info {struct f2fs_bio_info** write_io; } ;
struct f2fs_bio_info {int /*<<< orphan*/  io_rwsem; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  enum temp_type { ____Placeholder_temp_type } temp_type ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;

/* Variables and functions */
 int HOT ; 
 int META ; 
 int NR_TEMP_TYPE ; 
 int PAGE_TYPE_OF_BIO (int) ; 
 int __has_merged_page (struct f2fs_bio_info*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool has_merged_page(struct f2fs_sb_info *sbi, struct inode *inode,
				nid_t ino, pgoff_t idx, enum page_type type)
{
	enum page_type btype = PAGE_TYPE_OF_BIO(type);
	enum temp_type temp;
	struct f2fs_bio_info *io;
	bool ret = false;

	for (temp = HOT; temp < NR_TEMP_TYPE; temp++) {
		io = sbi->write_io[btype] + temp;

		down_read(&io->io_rwsem);
		ret = __has_merged_page(io, inode, ino, idx);
		up_read(&io->io_rwsem);

		/* TODO: use HOT temp only for meta pages now. */
		if (ret || btype == META)
			break;
	}
	return ret;
}
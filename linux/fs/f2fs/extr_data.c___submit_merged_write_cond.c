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
struct page {int dummy; } ;
struct inode {int dummy; } ;
struct f2fs_sb_info {struct f2fs_bio_info** write_io; } ;
struct f2fs_bio_info {int /*<<< orphan*/  io_rwsem; int /*<<< orphan*/  bio; } ;
typedef  int /*<<< orphan*/  nid_t ;
typedef  enum temp_type { ____Placeholder_temp_type } temp_type ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;

/* Variables and functions */
 int HOT ; 
 int META ; 
 int NR_TEMP_TYPE ; 
 int PAGE_TYPE_OF_BIO (int) ; 
 int /*<<< orphan*/  __f2fs_submit_merged_write (struct f2fs_sb_info*,int,int) ; 
 int __has_merged_page (int /*<<< orphan*/ ,struct inode*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __submit_merged_write_cond(struct f2fs_sb_info *sbi,
				struct inode *inode, struct page *page,
				nid_t ino, enum page_type type, bool force)
{
	enum temp_type temp;
	bool ret = true;

	for (temp = HOT; temp < NR_TEMP_TYPE; temp++) {
		if (!force)	{
			enum page_type btype = PAGE_TYPE_OF_BIO(type);
			struct f2fs_bio_info *io = sbi->write_io[btype] + temp;

			down_read(&io->io_rwsem);
			ret = __has_merged_page(io->bio, inode, page, ino);
			up_read(&io->io_rwsem);
		}
		if (ret)
			__f2fs_submit_merged_write(sbi, type, temp);

		/* TODO: use HOT temp only for meta pages now. */
		if (type >= META)
			break;
	}
}
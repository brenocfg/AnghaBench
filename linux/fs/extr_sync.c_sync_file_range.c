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
typedef  int /*<<< orphan*/  umode_t ;
struct file {struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESPIPE ; 
 int LLONG_MAX ; 
 int PAGE_SHIFT ; 
 unsigned int SYNC_FILE_RANGE_WAIT_AFTER ; 
 unsigned int SYNC_FILE_RANGE_WAIT_BEFORE ; 
 unsigned int SYNC_FILE_RANGE_WRITE ; 
 unsigned int SYNC_FILE_RANGE_WRITE_AND_WAIT ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 unsigned int VALID_FLAGS ; 
 int WB_SYNC_ALL ; 
 int WB_SYNC_NONE ; 
 int __filemap_fdatawrite_range (struct address_space*,int,int,int) ; 
 int file_fdatawait_range (struct file*,int,int) ; 
 TYPE_1__* file_inode (struct file*) ; 

int sync_file_range(struct file *file, loff_t offset, loff_t nbytes,
		    unsigned int flags)
{
	int ret;
	struct address_space *mapping;
	loff_t endbyte;			/* inclusive */
	umode_t i_mode;

	ret = -EINVAL;
	if (flags & ~VALID_FLAGS)
		goto out;

	endbyte = offset + nbytes;

	if ((s64)offset < 0)
		goto out;
	if ((s64)endbyte < 0)
		goto out;
	if (endbyte < offset)
		goto out;

	if (sizeof(pgoff_t) == 4) {
		if (offset >= (0x100000000ULL << PAGE_SHIFT)) {
			/*
			 * The range starts outside a 32 bit machine's
			 * pagecache addressing capabilities.  Let it "succeed"
			 */
			ret = 0;
			goto out;
		}
		if (endbyte >= (0x100000000ULL << PAGE_SHIFT)) {
			/*
			 * Out to EOF
			 */
			nbytes = 0;
		}
	}

	if (nbytes == 0)
		endbyte = LLONG_MAX;
	else
		endbyte--;		/* inclusive */

	i_mode = file_inode(file)->i_mode;
	ret = -ESPIPE;
	if (!S_ISREG(i_mode) && !S_ISBLK(i_mode) && !S_ISDIR(i_mode) &&
			!S_ISLNK(i_mode))
		goto out;

	mapping = file->f_mapping;
	ret = 0;
	if (flags & SYNC_FILE_RANGE_WAIT_BEFORE) {
		ret = file_fdatawait_range(file, offset, endbyte);
		if (ret < 0)
			goto out;
	}

	if (flags & SYNC_FILE_RANGE_WRITE) {
		int sync_mode = WB_SYNC_NONE;

		if ((flags & SYNC_FILE_RANGE_WRITE_AND_WAIT) ==
			     SYNC_FILE_RANGE_WRITE_AND_WAIT)
			sync_mode = WB_SYNC_ALL;

		ret = __filemap_fdatawrite_range(mapping, offset, endbyte,
						 sync_mode);
		if (ret < 0)
			goto out;
	}

	if (flags & SYNC_FILE_RANGE_WAIT_AFTER)
		ret = file_fdatawait_range(file, offset, endbyte);

out:
	return ret;
}
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
struct iomap_ops {scalar_t__ (* iomap_begin ) (struct inode*,scalar_t__,scalar_t__,unsigned int,struct iomap*) ;scalar_t__ (* iomap_end ) (struct inode*,scalar_t__,scalar_t__,scalar_t__,unsigned int,struct iomap*) ;} ;
struct iomap {scalar_t__ offset; scalar_t__ length; int /*<<< orphan*/  member_0; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ (* iomap_actor_t ) (struct inode*,scalar_t__,scalar_t__,void*,struct iomap*) ;

/* Variables and functions */
 scalar_t__ EIO ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ stub1 (struct inode*,scalar_t__,scalar_t__,unsigned int,struct iomap*) ; 
 scalar_t__ stub2 (struct inode*,scalar_t__,scalar_t__,scalar_t__,unsigned int,struct iomap*) ; 

loff_t
iomap_apply(struct inode *inode, loff_t pos, loff_t length, unsigned flags,
		const struct iomap_ops *ops, void *data, iomap_actor_t actor)
{
	struct iomap iomap = { 0 };
	loff_t written = 0, ret;

	/*
	 * Need to map a range from start position for length bytes. This can
	 * span multiple pages - it is only guaranteed to return a range of a
	 * single type of pages (e.g. all into a hole, all mapped or all
	 * unwritten). Failure at this point has nothing to undo.
	 *
	 * If allocation is required for this range, reserve the space now so
	 * that the allocation is guaranteed to succeed later on. Once we copy
	 * the data into the page cache pages, then we cannot fail otherwise we
	 * expose transient stale data. If the reserve fails, we can safely
	 * back out at this point as there is nothing to undo.
	 */
	ret = ops->iomap_begin(inode, pos, length, flags, &iomap);
	if (ret)
		return ret;
	if (WARN_ON(iomap.offset > pos))
		return -EIO;
	if (WARN_ON(iomap.length == 0))
		return -EIO;

	/*
	 * Cut down the length to the one actually provided by the filesystem,
	 * as it might not be able to give us the whole size that we requested.
	 */
	if (iomap.offset + iomap.length < pos + length)
		length = iomap.offset + iomap.length - pos;

	/*
	 * Now that we have guaranteed that the space allocation will succeed.
	 * we can do the copy-in page by page without having to worry about
	 * failures exposing transient data.
	 */
	written = actor(inode, pos, length, data, &iomap);

	/*
	 * Now the data has been copied, commit the range we've copied.  This
	 * should not fail unless the filesystem has had a fatal error.
	 */
	if (ops->iomap_end) {
		ret = ops->iomap_end(inode, pos, length,
				     written > 0 ? written : 0,
				     flags, &iomap);
	}

	return written ? written : ret;
}
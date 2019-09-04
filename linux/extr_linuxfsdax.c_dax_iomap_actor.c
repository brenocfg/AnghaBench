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
struct iov_iter {int dummy; } ;
struct iomap {scalar_t__ type; int flags; struct dax_device* dax_dev; struct block_device* bdev; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct dax_device {int dummy; } ;
struct block_device {int dummy; } ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int loff_t ;

/* Variables and functions */
 size_t ALIGN (int,int) ; 
 unsigned int EFAULT ; 
 unsigned int EINTR ; 
 int EIO ; 
 int IOMAP_F_NEW ; 
 scalar_t__ IOMAP_HOLE ; 
 scalar_t__ IOMAP_MAPPED ; 
 scalar_t__ IOMAP_UNWRITTEN ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 unsigned int PFN_PHYS (unsigned int) ; 
 int /*<<< orphan*/  PHYS_PFN (size_t const) ; 
 scalar_t__ READ ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 scalar_t__ WRITE ; 
 unsigned int bdev_dax_pgoff (struct block_device*,int /*<<< orphan*/  const,size_t const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 size_t dax_copy_from_iter (struct dax_device*,int /*<<< orphan*/ ,void*,unsigned int,struct iov_iter*) ; 
 size_t dax_copy_to_iter (struct dax_device*,int /*<<< orphan*/ ,void*,unsigned int,struct iov_iter*) ; 
 unsigned int dax_direct_access (struct dax_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dax_iomap_sector (struct iomap*,int) ; 
 int dax_read_lock () ; 
 int /*<<< orphan*/  dax_read_unlock (int) ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  invalidate_inode_pages2_range (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ iov_iter_rw (struct iov_iter*) ; 
 int iov_iter_zero (int,struct iov_iter*) ; 
 int min (int,int) ; 

__attribute__((used)) static loff_t
dax_iomap_actor(struct inode *inode, loff_t pos, loff_t length, void *data,
		struct iomap *iomap)
{
	struct block_device *bdev = iomap->bdev;
	struct dax_device *dax_dev = iomap->dax_dev;
	struct iov_iter *iter = data;
	loff_t end = pos + length, done = 0;
	ssize_t ret = 0;
	size_t xfer;
	int id;

	if (iov_iter_rw(iter) == READ) {
		end = min(end, i_size_read(inode));
		if (pos >= end)
			return 0;

		if (iomap->type == IOMAP_HOLE || iomap->type == IOMAP_UNWRITTEN)
			return iov_iter_zero(min(length, end - pos), iter);
	}

	if (WARN_ON_ONCE(iomap->type != IOMAP_MAPPED))
		return -EIO;

	/*
	 * Write can allocate block for an area which has a hole page mapped
	 * into page tables. We have to tear down these mappings so that data
	 * written by write(2) is visible in mmap.
	 */
	if (iomap->flags & IOMAP_F_NEW) {
		invalidate_inode_pages2_range(inode->i_mapping,
					      pos >> PAGE_SHIFT,
					      (end - 1) >> PAGE_SHIFT);
	}

	id = dax_read_lock();
	while (pos < end) {
		unsigned offset = pos & (PAGE_SIZE - 1);
		const size_t size = ALIGN(length + offset, PAGE_SIZE);
		const sector_t sector = dax_iomap_sector(iomap, pos);
		ssize_t map_len;
		pgoff_t pgoff;
		void *kaddr;

		if (fatal_signal_pending(current)) {
			ret = -EINTR;
			break;
		}

		ret = bdev_dax_pgoff(bdev, sector, size, &pgoff);
		if (ret)
			break;

		map_len = dax_direct_access(dax_dev, pgoff, PHYS_PFN(size),
				&kaddr, NULL);
		if (map_len < 0) {
			ret = map_len;
			break;
		}

		map_len = PFN_PHYS(map_len);
		kaddr += offset;
		map_len -= offset;
		if (map_len > end - pos)
			map_len = end - pos;

		/*
		 * The userspace address for the memory copy has already been
		 * validated via access_ok() in either vfs_read() or
		 * vfs_write(), depending on which operation we are doing.
		 */
		if (iov_iter_rw(iter) == WRITE)
			xfer = dax_copy_from_iter(dax_dev, pgoff, kaddr,
					map_len, iter);
		else
			xfer = dax_copy_to_iter(dax_dev, pgoff, kaddr,
					map_len, iter);

		pos += xfer;
		length -= xfer;
		done += xfer;

		if (xfer == 0)
			ret = -EFAULT;
		if (xfer < map_len)
			break;
	}
	dax_read_unlock(id);

	return done ? done : ret;
}
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
struct iov_iter {int nr_segs; TYPE_1__* iov; } ;
struct btrfs_fs_info {int sectorsize; } ;
typedef  scalar_t__ ssize_t ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {scalar_t__ iov_base; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ READ ; 
 unsigned int iov_iter_alignment (struct iov_iter const*) ; 
 scalar_t__ iov_iter_rw (struct iov_iter const*) ; 
 int /*<<< orphan*/  iter_is_iovec (struct iov_iter const*) ; 

__attribute__((used)) static ssize_t check_direct_IO(struct btrfs_fs_info *fs_info,
			       const struct iov_iter *iter, loff_t offset)
{
	int seg;
	int i;
	unsigned int blocksize_mask = fs_info->sectorsize - 1;
	ssize_t retval = -EINVAL;

	if (offset & blocksize_mask)
		goto out;

	if (iov_iter_alignment(iter) & blocksize_mask)
		goto out;

	/* If this is a write we don't need to check anymore */
	if (iov_iter_rw(iter) != READ || !iter_is_iovec(iter))
		return 0;
	/*
	 * Check to make sure we don't have duplicate iov_base's in this
	 * iovec, if so return EINVAL, otherwise we'll get csum errors
	 * when reading back.
	 */
	for (seg = 0; seg < iter->nr_segs; seg++) {
		for (i = seg + 1; i < iter->nr_segs; i++) {
			if (iter->iov[seg].iov_base == iter->iov[i].iov_base)
				goto out;
		}
	}
	retval = 0;
out:
	return retval;
}
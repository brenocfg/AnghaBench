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
struct iomap_page {int /*<<< orphan*/  write_count; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct bio_vec {int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageError (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_page_writeback (int /*<<< orphan*/ ) ; 
 scalar_t__ i_blocksize (struct inode*) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iomap_page* to_iomap_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_finish_page_writeback(
	struct inode		*inode,
	struct bio_vec	*bvec,
	int			error)
{
	struct iomap_page	*iop = to_iomap_page(bvec->bv_page);

	if (error) {
		SetPageError(bvec->bv_page);
		mapping_set_error(inode->i_mapping, -EIO);
	}

	ASSERT(iop || i_blocksize(inode) == PAGE_SIZE);
	ASSERT(!iop || atomic_read(&iop->write_count) > 0);

	if (!iop || atomic_dec_and_test(&iop->write_count))
		end_page_writeback(bvec->bv_page);
}
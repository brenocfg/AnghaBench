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
struct writeback_control {int dummy; } ;
struct swap_info_struct {int flags; int /*<<< orphan*/  bdev; struct file* swap_file; } ;
struct page {int dummy; } ;
struct kiocb {int /*<<< orphan*/  ki_pos; } ;
struct iov_iter {int dummy; } ;
struct file {struct address_space* f_mapping; } ;
struct bio_vec {int bv_len; int /*<<< orphan*/  bv_offset; struct page* bv_page; } ;
struct bio {int bi_opf; } ;
struct address_space {TYPE_1__* a_ops; } ;
typedef  int /*<<< orphan*/  bio_end_io_t ;
struct TYPE_2__ {int (* direct_IO ) (struct kiocb*,struct iov_iter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReclaim (struct page*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PSWPOUT ; 
 int /*<<< orphan*/  PageSwapCache (struct page*) ; 
 int REQ_OP_WRITE ; 
 int REQ_SWAP ; 
 int SWP_FS ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  WRITE ; 
 int bdev_write_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct page*,struct writeback_control*) ; 
 int /*<<< orphan*/  bio_associate_blkg_from_page (struct bio*,struct page*) ; 
 int /*<<< orphan*/  count_swpout_vm_event (struct page*) ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 
 struct bio* get_swap_bio (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sync_kiocb (struct kiocb*,struct file*) ; 
 int /*<<< orphan*/  iov_iter_bvec (struct iov_iter*,int /*<<< orphan*/ ,struct bio_vec*,int,int) ; 
 int /*<<< orphan*/  page_file_offset (struct page*) ; 
 struct swap_info_struct* page_swap_info (struct page*) ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  set_page_writeback (struct page*) ; 
 int stub1 (struct kiocb*,struct iov_iter*) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 int /*<<< orphan*/  swap_page_sector (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int wbc_to_write_flags (struct writeback_control*) ; 

int __swap_writepage(struct page *page, struct writeback_control *wbc,
		bio_end_io_t end_write_func)
{
	struct bio *bio;
	int ret;
	struct swap_info_struct *sis = page_swap_info(page);

	VM_BUG_ON_PAGE(!PageSwapCache(page), page);
	if (sis->flags & SWP_FS) {
		struct kiocb kiocb;
		struct file *swap_file = sis->swap_file;
		struct address_space *mapping = swap_file->f_mapping;
		struct bio_vec bv = {
			.bv_page = page,
			.bv_len  = PAGE_SIZE,
			.bv_offset = 0
		};
		struct iov_iter from;

		iov_iter_bvec(&from, WRITE, &bv, 1, PAGE_SIZE);
		init_sync_kiocb(&kiocb, swap_file);
		kiocb.ki_pos = page_file_offset(page);

		set_page_writeback(page);
		unlock_page(page);
		ret = mapping->a_ops->direct_IO(&kiocb, &from);
		if (ret == PAGE_SIZE) {
			count_vm_event(PSWPOUT);
			ret = 0;
		} else {
			/*
			 * In the case of swap-over-nfs, this can be a
			 * temporary failure if the system has limited
			 * memory for allocating transmit buffers.
			 * Mark the page dirty and avoid
			 * rotate_reclaimable_page but rate-limit the
			 * messages but do not flag PageError like
			 * the normal direct-to-bio case as it could
			 * be temporary.
			 */
			set_page_dirty(page);
			ClearPageReclaim(page);
			pr_err_ratelimited("Write error on dio swapfile (%llu)\n",
					   page_file_offset(page));
		}
		end_page_writeback(page);
		return ret;
	}

	ret = bdev_write_page(sis->bdev, swap_page_sector(page), page, wbc);
	if (!ret) {
		count_swpout_vm_event(page);
		return 0;
	}

	ret = 0;
	bio = get_swap_bio(GFP_NOIO, page, end_write_func);
	if (bio == NULL) {
		set_page_dirty(page);
		unlock_page(page);
		ret = -ENOMEM;
		goto out;
	}
	bio->bi_opf = REQ_OP_WRITE | REQ_SWAP | wbc_to_write_flags(wbc);
	bio_associate_blkg_from_page(bio, page);
	count_swpout_vm_event(page);
	set_page_writeback(page);
	unlock_page(page);
	submit_bio(bio);
out:
	return ret;
}
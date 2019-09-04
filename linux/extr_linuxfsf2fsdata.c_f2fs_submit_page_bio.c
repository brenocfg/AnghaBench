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
struct f2fs_io_info {int /*<<< orphan*/  type; int /*<<< orphan*/  sbi; struct page* page; int /*<<< orphan*/  op; int /*<<< orphan*/  op_flags; scalar_t__ io_wbc; int /*<<< orphan*/  temp; int /*<<< orphan*/  new_blkaddr; struct page* encrypted_page; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_GENERIC ; 
 int EFAULT ; 
 int /*<<< orphan*/  META_GENERIC ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  WB_DATA_TYPE (struct page*) ; 
 struct bio* __bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __is_meta_io (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  __submit_bio (int /*<<< orphan*/ ,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_add_page (struct bio*,struct page*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_is_valid_blkaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_trace_ios (struct f2fs_io_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_page_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_read_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_submit_page_bio (struct page*,struct f2fs_io_info*) ; 
 int /*<<< orphan*/  wbc_account_io (scalar_t__,struct page*,scalar_t__) ; 

int f2fs_submit_page_bio(struct f2fs_io_info *fio)
{
	struct bio *bio;
	struct page *page = fio->encrypted_page ?
			fio->encrypted_page : fio->page;

	if (!f2fs_is_valid_blkaddr(fio->sbi, fio->new_blkaddr,
			__is_meta_io(fio) ? META_GENERIC : DATA_GENERIC))
		return -EFAULT;

	trace_f2fs_submit_page_bio(page, fio);
	f2fs_trace_ios(fio, 0);

	/* Allocate a new bio */
	bio = __bio_alloc(fio->sbi, fio->new_blkaddr, fio->io_wbc,
				1, is_read_io(fio->op), fio->type, fio->temp);

	if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE) {
		bio_put(bio);
		return -EFAULT;
	}

	if (fio->io_wbc && !is_read_io(fio->op))
		wbc_account_io(fio->io_wbc, page, PAGE_SIZE);

	bio_set_op_attrs(bio, fio->op, fio->op_flags);

	if (!is_read_io(fio->op))
		inc_page_count(fio->sbi, WB_DATA_TYPE(fio->page));

	__submit_bio(fio->sbi, bio, fio->type);
	return 0;
}
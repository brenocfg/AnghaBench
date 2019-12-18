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
struct z3fold_pool {int dummy; } ;
struct z3fold_header {int start_middle; int /*<<< orphan*/  mapped_count; } ;
struct page {int /*<<< orphan*/  private; } ;
typedef  enum buddy { ____Placeholder_buddy } buddy ;

/* Variables and functions */
 int CHUNK_SHIFT ; 
#define  FIRST 130 
#define  LAST 129 
#define  MIDDLE 128 
 int /*<<< orphan*/  MIDDLE_CHUNK_MAPPED ; 
 int /*<<< orphan*/  PAGE_HEADLESS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZHDR_SIZE_ALIGNED ; 
 int handle_to_buddy (unsigned long) ; 
 int handle_to_chunks (unsigned long) ; 
 struct z3fold_header* handle_to_z3fold_header (unsigned long) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 

__attribute__((used)) static void *z3fold_map(struct z3fold_pool *pool, unsigned long handle)
{
	struct z3fold_header *zhdr;
	struct page *page;
	void *addr;
	enum buddy buddy;

	zhdr = handle_to_z3fold_header(handle);
	addr = zhdr;
	page = virt_to_page(zhdr);

	if (test_bit(PAGE_HEADLESS, &page->private))
		goto out;

	z3fold_page_lock(zhdr);
	buddy = handle_to_buddy(handle);
	switch (buddy) {
	case FIRST:
		addr += ZHDR_SIZE_ALIGNED;
		break;
	case MIDDLE:
		addr += zhdr->start_middle << CHUNK_SHIFT;
		set_bit(MIDDLE_CHUNK_MAPPED, &page->private);
		break;
	case LAST:
		addr += PAGE_SIZE - (handle_to_chunks(handle) << CHUNK_SHIFT);
		break;
	default:
		pr_err("unknown buddy id %d\n", buddy);
		WARN_ON(1);
		addr = NULL;
		break;
	}

	if (addr)
		zhdr->mapped_count++;
	z3fold_page_unlock(zhdr);
out:
	return addr;
}
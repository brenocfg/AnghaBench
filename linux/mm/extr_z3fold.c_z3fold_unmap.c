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
struct z3fold_header {int /*<<< orphan*/  mapped_count; } ;
struct page {int /*<<< orphan*/  private; } ;
typedef  enum buddy { ____Placeholder_buddy } buddy ;

/* Variables and functions */
 int MIDDLE ; 
 int /*<<< orphan*/  MIDDLE_CHUNK_MAPPED ; 
 int /*<<< orphan*/  PAGE_HEADLESS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int handle_to_buddy (unsigned long) ; 
 struct z3fold_header* handle_to_z3fold_header (unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct page* virt_to_page (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_lock (struct z3fold_header*) ; 
 int /*<<< orphan*/  z3fold_page_unlock (struct z3fold_header*) ; 

__attribute__((used)) static void z3fold_unmap(struct z3fold_pool *pool, unsigned long handle)
{
	struct z3fold_header *zhdr;
	struct page *page;
	enum buddy buddy;

	zhdr = handle_to_z3fold_header(handle);
	page = virt_to_page(zhdr);

	if (test_bit(PAGE_HEADLESS, &page->private))
		return;

	z3fold_page_lock(zhdr);
	buddy = handle_to_buddy(handle);
	if (buddy == MIDDLE)
		clear_bit(MIDDLE_CHUNK_MAPPED, &page->private);
	zhdr->mapped_count--;
	z3fold_page_unlock(zhdr);
}
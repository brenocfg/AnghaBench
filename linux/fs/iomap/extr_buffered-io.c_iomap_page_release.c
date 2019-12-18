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
struct iomap_page {int /*<<< orphan*/  write_count; int /*<<< orphan*/  read_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPagePrivate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iomap_page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,int /*<<< orphan*/ ) ; 
 struct iomap_page* to_iomap_page (struct page*) ; 

__attribute__((used)) static void
iomap_page_release(struct page *page)
{
	struct iomap_page *iop = to_iomap_page(page);

	if (!iop)
		return;
	WARN_ON_ONCE(atomic_read(&iop->read_count));
	WARN_ON_ONCE(atomic_read(&iop->write_count));
	ClearPagePrivate(page);
	set_page_private(page, 0);
	put_page(page);
	kfree(iop);
}
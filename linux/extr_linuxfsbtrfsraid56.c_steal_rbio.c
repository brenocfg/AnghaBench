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
struct btrfs_raid_bio {int nr_pages; struct page** stripe_pages; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  RBIO_CACHE_READY_BIT ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void steal_rbio(struct btrfs_raid_bio *src, struct btrfs_raid_bio *dest)
{
	int i;
	struct page *s;
	struct page *d;

	if (!test_bit(RBIO_CACHE_READY_BIT, &src->flags))
		return;

	for (i = 0; i < dest->nr_pages; i++) {
		s = src->stripe_pages[i];
		if (!s || !PageUptodate(s)) {
			continue;
		}

		d = dest->stripe_pages[i];
		if (d)
			__free_page(d);

		dest->stripe_pages[i] = s;
		src->stripe_pages[i] = NULL;
	}
}
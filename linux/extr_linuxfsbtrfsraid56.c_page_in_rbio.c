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
struct btrfs_raid_bio {int stripe_len; struct page** stripe_pages; int /*<<< orphan*/  bio_list_lock; struct page** bio_pages; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct page *page_in_rbio(struct btrfs_raid_bio *rbio,
				 int index, int pagenr, int bio_list_only)
{
	int chunk_page;
	struct page *p = NULL;

	chunk_page = index * (rbio->stripe_len >> PAGE_SHIFT) + pagenr;

	spin_lock_irq(&rbio->bio_list_lock);
	p = rbio->bio_pages[chunk_page];
	spin_unlock_irq(&rbio->bio_list_lock);

	if (p || bio_list_only)
		return p;

	return rbio->stripe_pages[chunk_page];
}
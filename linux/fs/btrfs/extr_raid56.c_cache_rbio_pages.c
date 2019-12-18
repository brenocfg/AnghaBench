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
struct btrfs_raid_bio {int nr_pages; int /*<<< orphan*/  flags; int /*<<< orphan*/ * stripe_pages; int /*<<< orphan*/ * bio_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  RBIO_CACHE_READY_BIT ; 
 int /*<<< orphan*/  SetPageUptodate (int /*<<< orphan*/ ) ; 
 int alloc_rbio_pages (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  copy_page (char*,char*) ; 
 char* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cache_rbio_pages(struct btrfs_raid_bio *rbio)
{
	int i;
	char *s;
	char *d;
	int ret;

	ret = alloc_rbio_pages(rbio);
	if (ret)
		return;

	for (i = 0; i < rbio->nr_pages; i++) {
		if (!rbio->bio_pages[i])
			continue;

		s = kmap(rbio->bio_pages[i]);
		d = kmap(rbio->stripe_pages[i]);

		copy_page(d, s);

		kunmap(rbio->bio_pages[i]);
		kunmap(rbio->stripe_pages[i]);
		SetPageUptodate(rbio->stripe_pages[i]);
	}
	set_bit(RBIO_CACHE_READY_BIT, &rbio->flags);
}
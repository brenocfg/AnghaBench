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
typedef  scalar_t__ u64 ;
struct page {int dummy; } ;
struct btrfs_raid_bio {int stripe_len; int nr_data; struct page** bio_pages; TYPE_1__* bbio; } ;
struct TYPE_2__ {scalar_t__* raid_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 

void raid56_add_scrub_pages(struct btrfs_raid_bio *rbio, struct page *page,
			    u64 logical)
{
	int stripe_offset;
	int index;

	ASSERT(logical >= rbio->bbio->raid_map[0]);
	ASSERT(logical + PAGE_SIZE <= rbio->bbio->raid_map[0] +
				rbio->stripe_len * rbio->nr_data);
	stripe_offset = (int)(logical - rbio->bbio->raid_map[0]);
	index = stripe_offset >> PAGE_SHIFT;
	rbio->bio_pages[index] = page;
}
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
struct btrfs_raid_bio {struct page** stripe_pages; } ;

/* Variables and functions */
 size_t rbio_stripe_page_index (struct btrfs_raid_bio*,int,int) ; 

__attribute__((used)) static struct page *rbio_stripe_page(struct btrfs_raid_bio *rbio, int stripe,
				     int index)
{
	return rbio->stripe_pages[rbio_stripe_page_index(rbio, stripe, index)];
}
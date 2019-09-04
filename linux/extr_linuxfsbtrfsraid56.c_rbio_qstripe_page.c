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
struct btrfs_raid_bio {scalar_t__ nr_data; scalar_t__ real_stripes; } ;

/* Variables and functions */
 struct page* rbio_stripe_page (struct btrfs_raid_bio*,scalar_t__,int) ; 

__attribute__((used)) static struct page *rbio_qstripe_page(struct btrfs_raid_bio *rbio, int index)
{
	if (rbio->nr_data + 1 == rbio->real_stripes)
		return NULL;
	return rbio_stripe_page(rbio, rbio->nr_data + 1, index);
}
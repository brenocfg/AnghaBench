#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct scrub_page {TYPE_2__* recover; } ;
struct TYPE_4__ {TYPE_1__* bbio; } ;
struct TYPE_3__ {int map_type; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_RAID56_MASK ; 

__attribute__((used)) static inline int scrub_is_page_on_raid56(struct scrub_page *page)
{
	return page->recover &&
	       (page->recover->bbio->map_type & BTRFS_BLOCK_GROUP_RAID56_MASK);
}
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
struct extent_buffer {int dummy; } ;
struct btrfs_dev_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_device_bytes_used (struct extent_buffer*,struct btrfs_dev_item*) ; 
 int /*<<< orphan*/  btrfs_device_id (struct extent_buffer*,struct btrfs_dev_item*) ; 
 int /*<<< orphan*/  btrfs_device_total_bytes (struct extent_buffer*,struct btrfs_dev_item*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_dev_item(struct extent_buffer *eb,
			   struct btrfs_dev_item *dev_item)
{
	pr_info("\t\tdev item devid %llu total_bytes %llu bytes used %llu\n",
	       btrfs_device_id(eb, dev_item),
	       btrfs_device_total_bytes(eb, dev_item),
	       btrfs_device_bytes_used(eb, dev_item));
}
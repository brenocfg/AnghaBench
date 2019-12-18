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
struct extent_buffer {int /*<<< orphan*/  start; } ;
struct btrfs_root_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_header_generation (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_level (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_root_bytenr (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_root_generation (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_root_level (struct btrfs_root_item*,int /*<<< orphan*/ ) ; 

void btrfs_set_root_node(struct btrfs_root_item *item,
			 struct extent_buffer *node)
{
	btrfs_set_root_bytenr(item, node->start);
	btrfs_set_root_level(item, btrfs_header_level(node));
	btrfs_set_root_generation(item, btrfs_header_generation(node));
}
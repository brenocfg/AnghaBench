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
struct btrfs_extent_data_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_extent_data_ref_count (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  btrfs_extent_data_ref_objectid (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  btrfs_extent_data_ref_offset (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  btrfs_extent_data_ref_root (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  pr_cont (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_extent_data_ref(struct extent_buffer *eb,
				  struct btrfs_extent_data_ref *ref)
{
	pr_cont("extent data backref root %llu objectid %llu offset %llu count %u\n",
	       btrfs_extent_data_ref_root(eb, ref),
	       btrfs_extent_data_ref_objectid(eb, ref),
	       btrfs_extent_data_ref_offset(eb, ref),
	       btrfs_extent_data_ref_count(eb, ref));
}
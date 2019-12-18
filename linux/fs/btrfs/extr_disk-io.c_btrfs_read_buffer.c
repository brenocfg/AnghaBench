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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int btree_read_extent_buffer_pages (struct extent_buffer*,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

int btrfs_read_buffer(struct extent_buffer *buf, u64 parent_transid, int level,
		      struct btrfs_key *first_key)
{
	return btree_read_extent_buffer_pages(buf, parent_transid,
					      level, first_key);
}
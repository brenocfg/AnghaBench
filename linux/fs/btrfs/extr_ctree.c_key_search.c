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
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int btrfs_bin_search (struct extent_buffer*,struct btrfs_key const*,int,int*) ; 

__attribute__((used)) static int key_search(struct extent_buffer *b, const struct btrfs_key *key,
		      int level, int *prev_cmp, int *slot)
{
	if (*prev_cmp != 0) {
		*prev_cmp = btrfs_bin_search(b, key, level, slot);
		return *prev_cmp;
	}

	*slot = 0;

	return 0;
}
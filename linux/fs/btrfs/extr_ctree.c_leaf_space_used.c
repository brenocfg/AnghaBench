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
struct btrfs_map_token {int dummy; } ;
struct btrfs_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_init_map_token (struct btrfs_map_token*,struct extent_buffer*) ; 
 struct btrfs_item* btrfs_item_nr (int) ; 
 int btrfs_token_item_offset (struct extent_buffer*,struct btrfs_item*,struct btrfs_map_token*) ; 
 int btrfs_token_item_size (struct extent_buffer*,struct btrfs_item*,struct btrfs_map_token*) ; 
 int min (int,int) ; 

__attribute__((used)) static int leaf_space_used(struct extent_buffer *l, int start, int nr)
{
	struct btrfs_item *start_item;
	struct btrfs_item *end_item;
	struct btrfs_map_token token;
	int data_len;
	int nritems = btrfs_header_nritems(l);
	int end = min(nritems, start + nr) - 1;

	if (!nr)
		return 0;
	btrfs_init_map_token(&token, l);
	start_item = btrfs_item_nr(start);
	end_item = btrfs_item_nr(end);
	data_len = btrfs_token_item_offset(l, start_item, &token) +
		btrfs_token_item_size(l, start_item, &token);
	data_len = data_len - btrfs_token_item_offset(l, end_item, &token);
	data_len += sizeof(struct btrfs_item) * nr;
	WARN_ON(data_len < 0);
	return data_len;
}
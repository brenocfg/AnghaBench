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
struct btrfs_chunk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_chunk_length (struct extent_buffer*,struct btrfs_chunk*) ; 
 int btrfs_chunk_num_stripes (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_owner (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_chunk_type (struct extent_buffer*,struct btrfs_chunk*) ; 
 int /*<<< orphan*/  btrfs_stripe_devid_nr (struct extent_buffer*,struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  btrfs_stripe_offset_nr (struct extent_buffer*,struct btrfs_chunk*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void print_chunk(struct extent_buffer *eb, struct btrfs_chunk *chunk)
{
	int num_stripes = btrfs_chunk_num_stripes(eb, chunk);
	int i;
	pr_info("\t\tchunk length %llu owner %llu type %llu num_stripes %d\n",
	       btrfs_chunk_length(eb, chunk), btrfs_chunk_owner(eb, chunk),
	       btrfs_chunk_type(eb, chunk), num_stripes);
	for (i = 0 ; i < num_stripes ; i++) {
		pr_info("\t\t\tstripe %d devid %llu offset %llu\n", i,
		      btrfs_stripe_devid_nr(eb, chunk, i),
		      btrfs_stripe_offset_nr(eb, chunk, i));
	}
}
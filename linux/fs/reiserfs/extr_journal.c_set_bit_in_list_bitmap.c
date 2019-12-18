#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_blocksize; } ;
struct reiserfs_list_bitmap {TYPE_1__** bitmaps; } ;
typedef  int b_blocknr_t ;
struct TYPE_2__ {scalar_t__ data; } ;

/* Variables and functions */
 TYPE_1__* get_bitmap_node (struct super_block*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static int set_bit_in_list_bitmap(struct super_block *sb,
				  b_blocknr_t block,
				  struct reiserfs_list_bitmap *jb)
{
	unsigned int bmap_nr = block / (sb->s_blocksize << 3);
	unsigned int bit_nr = block % (sb->s_blocksize << 3);

	if (!jb->bitmaps[bmap_nr]) {
		jb->bitmaps[bmap_nr] = get_bitmap_node(sb);
	}
	set_bit(bit_nr, (unsigned long *)jb->bitmaps[bmap_nr]->data);
	return 0;
}
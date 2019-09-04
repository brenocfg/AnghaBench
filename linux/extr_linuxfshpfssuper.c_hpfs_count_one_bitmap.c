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
struct super_block {int dummy; } ;
struct quad_buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  secno ;

/* Variables and functions */
 int BITS_PER_BYTE ; 
 unsigned int bitmap_weight (unsigned long*,int) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 unsigned long* hpfs_map_4sectors (struct super_block*,int /*<<< orphan*/ ,struct quad_buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned hpfs_count_one_bitmap(struct super_block *s, secno secno)
{
	struct quad_buffer_head qbh;
	unsigned long *bits;
	unsigned count;

	bits = hpfs_map_4sectors(s, secno, &qbh, 0);
	if (!bits)
		return (unsigned)-1;
	count = bitmap_weight(bits, 2048 * BITS_PER_BYTE);
	hpfs_brelse4(&qbh);
	return count;
}
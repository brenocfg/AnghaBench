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
struct dblock {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ BLOCK_END ; 
 scalar_t__ dblock_addr (struct dblock const*) ; 
 int dblock_len (struct dblock const*) ; 

size_t
hermes_blocks_length(const char *first_block, const void *end)
{
	const struct dblock *blk = (const struct dblock *) first_block;
	int total_len = 0;
	int len;

	end -= sizeof(*blk);

	/* Skip all blocks to locate Plug Data References
	 * (Spectrum CS) */
	while (((void *) blk <= end) &&
	       (dblock_addr(blk) != BLOCK_END)) {
		len = dblock_len(blk);
		total_len += sizeof(*blk) + len;
		blk = (struct dblock *) &blk->data[len];
	}

	return total_len;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct fw_block {int dummy; } ;
struct TYPE_4__ {scalar_t__ romio_offs; } ;
struct TYPE_3__ {scalar_t__ file_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_TYPE_RAW ; 
 int block_stat_file (struct fw_block*) ; 
 struct fw_block* blocks ; 
 TYPE_2__* board ; 
 TYPE_1__* bootext_block ; 
 int calc_block_offsets (int /*<<< orphan*/ ,scalar_t__*) ; 
 int num_blocks ; 

int
process_blocks(void)
{
	struct fw_block *block;
	uint32_t offset;
	int i;
	int res;

	/* collecting file stats */
	for (i = 0; i < num_blocks; i++) {
		block = &blocks[i];
		res = block_stat_file(block);
		if (res)
			return res;
	}

	offset = board->romio_offs + bootext_block->file_size;
	res = calc_block_offsets(BLOCK_TYPE_RAW, &offset);

	return res;
}
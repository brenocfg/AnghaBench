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
typedef  int uint32_t ;
struct mylo_partition_table {int dummy; } ;
struct mylo_partition_header {int dummy; } ;
struct mylo_fw_blockdesc {void* blen; void* dlen; void* addr; void* type; } ;
struct fw_block {int size; int flags; int addr; int blocklen; } ;
typedef  int /*<<< orphan*/  desc ;
struct TYPE_2__ {int part_offset; int part_size; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int BLOCK_FLAG_HAVEHDR ; 
 int FW_DESC_TYPE_USED ; 
 void* HOST_TO_LE32 (int) ; 
 int MYLO_MAX_PARTITIONS ; 
 int PART_NAME_LEN ; 
 TYPE_1__* board ; 
 struct fw_block* fw_blocks ; 
 int fw_num_blocks ; 
 scalar_t__ fw_num_partitions ; 
 int /*<<< orphan*/  memset (struct mylo_fw_blockdesc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ write_out_desc (int /*<<< orphan*/ *,struct mylo_fw_blockdesc*,int*) ; 
 scalar_t__ write_out_file (int /*<<< orphan*/ *,struct fw_block*,int*) ; 
 scalar_t__ write_out_partitions (int /*<<< orphan*/ *,int*) ; 

int
write_out_blocks(FILE *outfile, uint32_t *crc)
{
	struct mylo_fw_blockdesc desc;
	struct fw_block *b;
	uint32_t dlen;
	int i;

	/*
	 * if at least one partition specified, write out block descriptor
	 * for the partition table
	 */
	if (fw_num_partitions > 0) {
		desc.type = HOST_TO_LE32(FW_DESC_TYPE_USED);
		desc.addr = HOST_TO_LE32(board->part_offset);
		desc.dlen = HOST_TO_LE32(sizeof(struct mylo_partition_table) +
					(MYLO_MAX_PARTITIONS * PART_NAME_LEN));
		desc.blen = HOST_TO_LE32(board->part_size);

		if (write_out_desc(outfile, &desc, crc) != 0)
		        return -1;
	}

	/*
	 * write out block descriptors for each files
	 */
	for (i = 0; i < fw_num_blocks; i++) {
		b = &fw_blocks[i];

		/* detect block size */
		dlen = b->size;
		if ((b->flags & BLOCK_FLAG_HAVEHDR) != 0) {
			dlen += sizeof(struct mylo_partition_header);
		}

		/* round up to 4 bytes */
		dlen = ALIGN(dlen, 4);

		/* setup the descriptor */
		desc.type = HOST_TO_LE32(FW_DESC_TYPE_USED);
		desc.addr = HOST_TO_LE32(b->addr);
		desc.dlen = HOST_TO_LE32(dlen);
		desc.blen = HOST_TO_LE32(b->blocklen);

		if (write_out_desc(outfile, &desc, crc) != 0)
			return -1;
	}

	/*
	 * write out the null block descriptor
	 */
	memset(&desc, 0, sizeof(desc));
	if (write_out_desc(outfile, &desc, crc) != 0)
		return -1;

	if (write_out_partitions(outfile, crc) != 0)
		return -1;

	/*
	 * write out data for each blocks
	 */
	for (i = 0; i < fw_num_blocks; i++) {
		b = &fw_blocks[i];
		if (write_out_file(outfile, b, crc) != 0)
		        return -1;
	}

	return 0;
}
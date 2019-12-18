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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocfs2_block_check {int /*<<< orphan*/  bc_ecc; int /*<<< orphan*/  bc_crc32e; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ crc32_le (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memset (struct ocfs2_block_check*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ocfs2_hamming_encode_block (void*,size_t) ; 

void ocfs2_block_check_compute(void *data, size_t blocksize,
			       struct ocfs2_block_check *bc)
{
	u32 crc;
	u32 ecc;

	memset(bc, 0, sizeof(struct ocfs2_block_check));

	crc = crc32_le(~0, data, blocksize);
	ecc = ocfs2_hamming_encode_block(data, blocksize);

	/*
	 * No ecc'd ocfs2 structure is larger than 4K, so ecc will be no
	 * larger than 16 bits.
	 */
	BUG_ON(ecc > USHRT_MAX);

	bc->bc_crc32e = cpu_to_le32(crc);
	bc->bc_ecc = cpu_to_le16((u16)ecc);
}
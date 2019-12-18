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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 scalar_t__ TFFS_BLOCK_HEADER_MAGIC ; 
 scalar_t__ TFFS_SECTORS_PER_PAGE ; 
 int /*<<< orphan*/  check_sector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_sector (int /*<<< orphan*/ ) ; 
 scalar_t__ read_uint32 (int /*<<< orphan*/ ,int) ; 
 int read_uint64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readbuf ; 
 int /*<<< orphan*/  sector_mark_bad (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int check_block(off_t pos, uint32_t sector)
{
	if (!check_sector(pos)) {
		return 0;
	}
	if (read_sector(pos)) {
		return 0;
	}
	if (read_uint64(readbuf, 0x00) != TFFS_BLOCK_HEADER_MAGIC) {
		fprintf(stderr, "Warning: block without magic header. Skipping block\n");
		return 0;
	}
	if (read_uint32(readbuf, 0x0c) != TFFS_SECTORS_PER_PAGE) {
		fprintf(stderr, "Warning: block with wrong number of sectors per page. Skipping block\n");
		return 0;
	}

	uint32_t num_hdr_bad = read_uint32(readbuf, 0x0c);
	for (uint32_t i = 0; i < num_hdr_bad; i++) {
		uint32_t bad = sector + read_uint64(readbuf, 0x1c + sizeof(uint64_t)*i);
		sector_mark_bad(bad);
	}

	return 1;
}
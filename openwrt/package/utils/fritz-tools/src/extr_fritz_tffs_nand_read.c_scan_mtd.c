#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct mtd_info_user {int erasesize; int size; } ;
typedef  int off_t ;
struct TYPE_3__ {int num_sectors; int /*<<< orphan*/  sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MEMGETINFO ; 
 int TFFS_SECTOR_SIZE ; 
 int blocksize ; 
 scalar_t__ check_block (int,int) ; 
 int /*<<< orphan*/  check_sector (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtd_info_user*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtdfd ; 
 int /*<<< orphan*/  sector_get_good (int) ; 
 int /*<<< orphan*/  sector_mark_bad (int) ; 
 TYPE_1__* sectors ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int scan_mtd(void)
{
	struct mtd_info_user info;

	if (ioctl(mtdfd, MEMGETINFO, &info)) {
		return 0;
	}

	blocksize = info.erasesize;

	sectors = malloc(sizeof(*sectors) + (info.size / TFFS_SECTOR_SIZE + 7) / 8);
	if (sectors == NULL) {
		fprintf(stderr, "ERROR: memory allocation failed!\n");
		exit(EXIT_FAILURE);
	}
	sectors->num_sectors = info.size / TFFS_SECTOR_SIZE;
	memset(sectors->sectors, 0xff, (info.size / TFFS_SECTOR_SIZE + 7) / 8);

	uint32_t sector = 0, valid_blocks = 0;
	uint8_t block_ok = 0;
	for (off_t pos = 0; pos < info.size; sector++, pos += TFFS_SECTOR_SIZE) {
		if (pos % info.erasesize == 0) {
			block_ok = check_block(pos, sector);
			/* first sector of the block contains metadata
			   => handle it like a bad sector */
			sector_mark_bad(sector);
			if (block_ok) {
				valid_blocks++;
			}
		} else if (!block_ok || !sector_get_good(sector) || !check_sector(pos)) {
			sector_mark_bad(sector);
		}
	}

	return valid_blocks;
}
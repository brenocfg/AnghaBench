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
typedef  size_t uint32_t ;
typedef  scalar_t__ UINT ;
typedef  int DWORD ;
typedef  scalar_t__ DRESULT ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FS_MODE_OPEN_READ ; 
 scalar_t__ RES_ERROR ; 
 scalar_t__ RES_OK ; 
 scalar_t__ RES_PARERR ; 
 int SFLASH_SECTORS_PER_BLOCK ; 
 scalar_t__ SFLASH_SECTOR_COUNT ; 
 size_t SFLASH_SECTOR_SIZE ; 
 scalar_t__ STA_NOINIT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  print_block_name (int) ; 
 int /*<<< orphan*/  sflash_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sflash_block_cache ; 
 scalar_t__ sflash_disk_flush () ; 
 int /*<<< orphan*/  sflash_init_done ; 
 int sflash_prblock ; 
 int sflash_ublock ; 
 int /*<<< orphan*/  sl_FsRead ; 

DRESULT sflash_disk_read(BYTE *buff, DWORD sector, UINT count) {
    uint32_t secindex;

    if (!sflash_init_done) {
        return STA_NOINIT;
    }

    if ((sector + count > SFLASH_SECTOR_COUNT) || (count == 0)) {
        return RES_PARERR;
    }

    for (int i = 0; i < count; i++) {
        secindex = (sector + i) % SFLASH_SECTORS_PER_BLOCK;
        sflash_ublock = (sector + i) / SFLASH_SECTORS_PER_BLOCK;
        // See if it's time to read a new block
        if (sflash_prblock != sflash_ublock) {
            if (sflash_disk_flush() != RES_OK) {
                return RES_ERROR;
            }
            sflash_prblock = sflash_ublock;
            print_block_name (sflash_ublock);
            if (!sflash_access(FS_MODE_OPEN_READ, sl_FsRead)) {
                return RES_ERROR;
            }
        }
        // Copy the requested sector from the block cache
        memcpy (buff, &sflash_block_cache[(secindex * SFLASH_SECTOR_SIZE)], SFLASH_SECTOR_SIZE);
        buff += SFLASH_SECTOR_SIZE;
    }
    return RES_OK;
}
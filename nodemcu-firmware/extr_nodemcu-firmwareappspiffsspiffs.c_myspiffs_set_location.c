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
typedef  int u32_t ;
struct TYPE_3__ {int phys_addr; int phys_size; int log_block_size; } ;
typedef  TYPE_1__ spiffs_config ;

/* Variables and functions */
 int FALSE ; 
 int INTERNAL_FLASH_SIZE ; 
 int MIN_BLOCKS_FS ; 
 scalar_t__ platform_flash_get_first_free_block_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool myspiffs_set_location(spiffs_config *cfg, int align, int offset, int block_size) {
#ifdef SPIFFS_FIXED_LOCATION
  cfg->phys_addr = (SPIFFS_FIXED_LOCATION + block_size - 1) & ~(block_size-1);
#else
  cfg->phys_addr = ( u32_t )platform_flash_get_first_free_block_address( NULL ) + offset;
  cfg->phys_addr = (cfg->phys_addr + align - 1) & ~(align - 1);
#endif
#ifdef SPIFFS_SIZE_1M_BOUNDARY
  cfg->phys_size = ((0x100000 - (SYS_PARAM_SEC_NUM * INTERNAL_FLASH_SECTOR_SIZE) - ( ( u32_t )cfg->phys_addr )) & ~(block_size - 1)) & 0xfffff;
#else
  cfg->phys_size = (INTERNAL_FLASH_SIZE - ( ( u32_t )cfg->phys_addr )) & ~(block_size - 1);
#endif
  if ((int) cfg->phys_size < 0) {
    return FALSE;
  }
  cfg->log_block_size = block_size;

  return (cfg->phys_size / block_size) >= MIN_BLOCKS_FS;
}
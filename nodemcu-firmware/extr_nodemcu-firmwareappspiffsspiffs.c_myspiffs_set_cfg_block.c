#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phys_size; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  hal_erase_f; int /*<<< orphan*/  hal_write_f; int /*<<< orphan*/  hal_read_f; int /*<<< orphan*/  log_page_size; int /*<<< orphan*/  phys_erase_block; } ;
typedef  TYPE_1__ spiffs_config ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  INTERNAL_FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  LOG_PAGE_SIZE ; 
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  my_spiffs_erase ; 
 int /*<<< orphan*/  my_spiffs_read ; 
 int /*<<< orphan*/  my_spiffs_write ; 
 int /*<<< orphan*/  myspiffs_set_location (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static bool myspiffs_set_cfg_block(spiffs_config *cfg, int align, int offset, int block_size, bool force_create) {
  cfg->phys_erase_block = INTERNAL_FLASH_SECTOR_SIZE; // according to datasheet
  cfg->log_page_size = LOG_PAGE_SIZE; // as we said

  cfg->hal_read_f = my_spiffs_read;
  cfg->hal_write_f = my_spiffs_write;
  cfg->hal_erase_f = my_spiffs_erase;

  if (!myspiffs_set_location(cfg, align, offset, block_size)) {
    return FALSE;
  }

  NODE_DBG("fs.start:%x,max:%x\n",cfg->phys_addr,cfg->phys_size);

#ifdef SPIFFS_USE_MAGIC_LENGTH
  if (force_create) {
    return TRUE;
  }

  int size = SPIFFS_probe_fs(cfg);

  if (size > 0 && size < cfg->phys_size) {
    NODE_DBG("Overriding size:%x\n",size);
    cfg->phys_size = size;
  }
  if (size > 0) {
    return TRUE;
  }
  return FALSE;
#else
  return TRUE;
#endif
}
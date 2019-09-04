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
struct TYPE_4__ {int phys_size; } ;
typedef  TYPE_1__ spiffs_config ;

/* Variables and functions */
 int FALSE ; 
 int INTERNAL_FLASH_SIZE ; 
 int LOG_BLOCK_SIZE ; 
 int TRUE ; 
 scalar_t__ myspiffs_set_cfg (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static bool myspiffs_find_cfg(spiffs_config *cfg, bool force_create) {
  int i;

  if (!force_create) {
#ifdef SPIFFS_FIXED_LOCATION
    if (myspiffs_set_cfg(cfg, 0, 0, FALSE)) {
      return TRUE;
    }
#else
    if (INTERNAL_FLASH_SIZE >= 700000) {
      for (i = 0; i < 8; i++) {
	if (myspiffs_set_cfg(cfg, 0x10000, 0x10000 * i, FALSE)) {
	  return TRUE;
	}
      }
    }

    for (i = 0; i < 8; i++) {
      if (myspiffs_set_cfg(cfg, LOG_BLOCK_SIZE, LOG_BLOCK_SIZE * i, FALSE)) {
	return TRUE;
      }
    }
#endif
  }

  // No existing file system -- set up for a format
  if (INTERNAL_FLASH_SIZE >= 700000) {
    myspiffs_set_cfg(cfg, 0x10000, 0x10000, TRUE);
#ifndef SPIFFS_MAX_FILESYSTEM_SIZE
    if (cfg->phys_size < 400000) {
      // Don't waste so much in alignment
      myspiffs_set_cfg(cfg, LOG_BLOCK_SIZE, LOG_BLOCK_SIZE * 4, TRUE);
    }
#endif
  } else {
    myspiffs_set_cfg(cfg, LOG_BLOCK_SIZE, 0, TRUE);
  }

#ifdef SPIFFS_MAX_FILESYSTEM_SIZE
  if (cfg->phys_size > SPIFFS_MAX_FILESYSTEM_SIZE) {
    cfg->phys_size = (SPIFFS_MAX_FILESYSTEM_SIZE) & ~(cfg->log_block_size - 1);
  }
#endif

  return FALSE;
}
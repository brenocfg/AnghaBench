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
typedef  int /*<<< orphan*/  spiffs_config ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_BLOCK_SIZE ; 
 int /*<<< orphan*/  LOG_BLOCK_SIZE_SMALL_FS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ myspiffs_set_cfg_block (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool myspiffs_set_cfg(spiffs_config *cfg, int align, int offset, bool force_create) {
  if (force_create) {
    return myspiffs_set_cfg_block(cfg, align, offset, LOG_BLOCK_SIZE         , TRUE) ||
           myspiffs_set_cfg_block(cfg, align, offset, LOG_BLOCK_SIZE_SMALL_FS, TRUE);
  }

  return myspiffs_set_cfg_block(cfg, align, offset, LOG_BLOCK_SIZE_SMALL_FS, FALSE) ||
         myspiffs_set_cfg_block(cfg, align, offset, LOG_BLOCK_SIZE         , FALSE);
}
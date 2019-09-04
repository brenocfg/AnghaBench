#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int spiffs_obj_id ;
struct TYPE_7__ {int (* hal_read_f ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int log_block_size; } ;
typedef  TYPE_1__ spiffs_config ;
typedef  int spiffs_block_ix ;
struct TYPE_8__ {scalar_t__ block_count; int /*<<< orphan*/  cfg; } ;
typedef  TYPE_2__ spiffs ;
typedef  int s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int) ; 
 int SPIFFS_ERR_PROBE_NOT_A_FS ; 
 int SPIFFS_ERR_PROBE_TOO_FEW_BLOCKS ; 
 int SPIFFS_MAGIC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_MAGIC_PADDR (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _SPIFFS_MEMCPY (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

s32_t spiffs_probe(
    spiffs_config *cfg) {
  s32_t res;
  u32_t paddr;
  spiffs dummy_fs; // create a dummy fs struct just to be able to use macros
  _SPIFFS_MEMCPY(&dummy_fs.cfg, cfg, sizeof(spiffs_config));
  dummy_fs.block_count = 0;

  // Read three magics, as one block may be in an aborted erase state.
  // At least two of these must contain magic and be in decreasing order.
  spiffs_obj_id magic[3];
  spiffs_obj_id bix_count[3];

  spiffs_block_ix bix;
  for (bix = 0; bix < 3; bix++) {
    paddr = SPIFFS_MAGIC_PADDR(&dummy_fs, bix);
#if SPIFFS_HAL_CALLBACK_EXTRA
    // not any proper fs to report here, so callback with null
    // (cross fingers that no-one gets angry)
    res = cfg->hal_read_f((void *)0, paddr, sizeof(spiffs_obj_id), (u8_t *)&magic[bix]);
#else
    res = cfg->hal_read_f(paddr, sizeof(spiffs_obj_id), (u8_t *)&magic[bix]);
#endif
    bix_count[bix] = magic[bix] ^ SPIFFS_MAGIC(&dummy_fs, 0);
    SPIFFS_CHECK_RES(res);
  }

  // check that we have sane number of blocks
  if (bix_count[0] < 3) return SPIFFS_ERR_PROBE_TOO_FEW_BLOCKS;
  // check that the order is correct, take aborted erases in calculation
  // first block aborted erase
  if (magic[0] == (spiffs_obj_id)(-1) && bix_count[1] - bix_count[2] == 1) {
    return (bix_count[1]+1) * cfg->log_block_size;
  }
  // second block aborted erase
  if (magic[1] == (spiffs_obj_id)(-1) && bix_count[0] - bix_count[2] == 2) {
    return bix_count[0] * cfg->log_block_size;
  }
  // third block aborted erase
  if (magic[2] == (spiffs_obj_id)(-1) && bix_count[0] - bix_count[1] == 1) {
    return bix_count[0] * cfg->log_block_size;
  }
  // no block has aborted erase
  if (bix_count[0] - bix_count[1] == 1 && bix_count[1] - bix_count[2] == 1) {
    return bix_count[0] * cfg->log_block_size;
  }

  return SPIFFS_ERR_PROBE_NOT_A_FS;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ spiffs_obj_id ;
typedef  scalar_t__ spiffs_block_ix ;
struct TYPE_6__ {scalar_t__ block_count; scalar_t__ stats_p_deleted; scalar_t__ stats_p_allocated; scalar_t__ free_blocks; scalar_t__ max_erase_count; } ;
typedef  TYPE_1__ spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 scalar_t__ MAX (scalar_t__,scalar_t__) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPIFFS_CHECK_RES (scalar_t__) ; 
 int /*<<< orphan*/  SPIFFS_ERASE_COUNT_PADDR (TYPE_1__*,scalar_t__) ; 
 scalar_t__ SPIFFS_OBJ_ID_FREE ; 
 scalar_t__ SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_T_OBJ_LU2 ; 
 scalar_t__ SPIFFS_VIS_END ; 
 scalar_t__ _spiffs_rd (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ spiffs_obj_lu_find_entry_visitor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int*) ; 
 int /*<<< orphan*/  spiffs_obj_lu_scan_v ; 

s32_t spiffs_obj_lu_scan(
    spiffs *fs) {
  s32_t res;
  spiffs_block_ix bix;
  int entry;
#if SPIFFS_USE_MAGIC
  spiffs_block_ix unerased_bix = (spiffs_block_ix)-1;
#endif

  // find out erase count
  // if enabled, check magic
  bix = 0;
  spiffs_obj_id erase_count_final;
  spiffs_obj_id erase_count_min = SPIFFS_OBJ_ID_FREE;
  spiffs_obj_id erase_count_max = 0;
  while (bix < fs->block_count) {
#if SPIFFS_USE_MAGIC
    spiffs_obj_id magic;
    res = _spiffs_rd(fs,
        SPIFFS_OP_T_OBJ_LU2 | SPIFFS_OP_C_READ,
        0, SPIFFS_MAGIC_PADDR(fs, bix) ,
        sizeof(spiffs_obj_id), (u8_t *)&magic);

    SPIFFS_CHECK_RES(res);
    if (magic != SPIFFS_MAGIC(fs, bix)) {
      if (unerased_bix == (spiffs_block_ix)-1) {
        // allow one unerased block as it might be powered down during an erase
        unerased_bix = bix;
      } else {
        // more than one unerased block, bail out
        SPIFFS_CHECK_RES(SPIFFS_ERR_NOT_A_FS);
      }
    }
#endif
    spiffs_obj_id erase_count;
    res = _spiffs_rd(fs,
        SPIFFS_OP_T_OBJ_LU2 | SPIFFS_OP_C_READ,
        0, SPIFFS_ERASE_COUNT_PADDR(fs, bix) ,
        sizeof(spiffs_obj_id), (u8_t *)&erase_count);
    SPIFFS_CHECK_RES(res);
    if (erase_count != SPIFFS_OBJ_ID_FREE) {
      erase_count_min = MIN(erase_count_min, erase_count);
      erase_count_max = MAX(erase_count_max, erase_count);
    }
    bix++;
  }

  if (erase_count_min == 0 && erase_count_max == SPIFFS_OBJ_ID_FREE) {
    // clean system, set counter to zero
    erase_count_final = 0;
  } else if (erase_count_max - erase_count_min > (SPIFFS_OBJ_ID_FREE)/2) {
    // wrap, take min
    erase_count_final = erase_count_min+1;
  } else {
    erase_count_final = erase_count_max+1;
  }

  fs->max_erase_count = erase_count_final;

#if SPIFFS_USE_MAGIC
  if (unerased_bix != (spiffs_block_ix)-1) {
    // found one unerased block, remedy
    SPIFFS_DBG("mount: erase block "_SPIPRIbl"\n", bix);
#if SPIFFS_READ_ONLY
    res = SPIFFS_ERR_RO_ABORTED_OPERATION;
#else
    res = spiffs_erase_block(fs, unerased_bix);
#endif // SPIFFS_READ_ONLY
    SPIFFS_CHECK_RES(res);
  }
#endif

  // count blocks

  fs->free_blocks = 0;
  fs->stats_p_allocated = 0;
  fs->stats_p_deleted = 0;

  res = spiffs_obj_lu_find_entry_visitor(fs,
      0,
      0,
      0,
      0,
      spiffs_obj_lu_scan_v,
      0,
      0,
      &bix,
      &entry);

  if (res == SPIFFS_VIS_END) {
    res = SPIFFS_OK;
  }

  SPIFFS_CHECK_RES(res);

  return res;
}
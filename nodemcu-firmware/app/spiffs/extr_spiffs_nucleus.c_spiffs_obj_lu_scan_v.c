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
typedef  scalar_t__ spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
struct TYPE_3__ {int /*<<< orphan*/  stats_p_allocated; int /*<<< orphan*/  stats_p_deleted; int /*<<< orphan*/  free_blocks; } ;
typedef  TYPE_1__ spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 scalar_t__ SPIFFS_OBJ_ID_DELETED ; 
 scalar_t__ SPIFFS_OBJ_ID_FREE ; 
 int /*<<< orphan*/  SPIFFS_VIS_COUNTINUE ; 

__attribute__((used)) static s32_t spiffs_obj_lu_scan_v(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_block_ix bix,
    int ix_entry,
    const void *user_const_p,
    void *user_var_p) {
  (void)bix;
  (void)user_const_p;
  (void)user_var_p;
  if (obj_id == SPIFFS_OBJ_ID_FREE) {
    if (ix_entry == 0) {
      fs->free_blocks++;
      // todo optimize further, return SPIFFS_NEXT_BLOCK
    }
  } else if (obj_id == SPIFFS_OBJ_ID_DELETED) {
    fs->stats_p_deleted++;
  } else {
    fs->stats_p_allocated++;
  }

  return SPIFFS_VIS_COUNTINUE;
}
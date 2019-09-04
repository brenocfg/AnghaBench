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
typedef  int /*<<< orphan*/  spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 scalar_t__ SPIFFS_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  SPIFFS_VIS_CHECK_ID ; 
 scalar_t__ SPIFFS_VIS_END ; 
 scalar_t__ spiffs_obj_lu_find_entry_visitor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 

s32_t spiffs_obj_lu_find_id(
    spiffs *fs,
    spiffs_block_ix starting_block,
    int starting_lu_entry,
    spiffs_obj_id obj_id,
    spiffs_block_ix *block_ix,
    int *lu_entry) {
  s32_t res = spiffs_obj_lu_find_entry_visitor(
      fs, starting_block, starting_lu_entry, SPIFFS_VIS_CHECK_ID, obj_id, 0, 0, 0, block_ix, lu_entry);
  if (res == SPIFFS_VIS_END) {
    res = SPIFFS_ERR_NOT_FOUND;
  }
  return res;
}
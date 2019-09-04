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
typedef  int /*<<< orphan*/  u32_t ;
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
typedef  TYPE_1__ spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CB (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_CFG_LOG_PAGE_SZ (TYPE_1__*) ; 
 int /*<<< orphan*/  SPIFFS_CHECK_ERROR ; 
 int /*<<< orphan*/  SPIFFS_CHECK_INDEX ; 
 int /*<<< orphan*/  SPIFFS_CHECK_PROGRESS ; 
 scalar_t__ SPIFFS_OK ; 
 scalar_t__ SPIFFS_VIS_END ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ spiffs_obj_lu_find_entry_visitor (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spiffs_object_index_consistency_check_v ; 

s32_t spiffs_object_index_consistency_check(spiffs *fs) {
  s32_t res = SPIFFS_OK;
  // impl note:
  // fs->work is used for a temporary object index memory, listing found object ids and
  // indicating whether they can be reached or not. Acting as a fifo if object ids cannot fit.
  // In the temporary object index memory, SPIFFS_OBJ_ID_IX_FLAG bit is used to indicate
  // a reachable/unreachable object id.
  memset(fs->work, 0, SPIFFS_CFG_LOG_PAGE_SZ(fs));
  u32_t obj_id_log_ix = 0;
  CHECK_CB(fs, SPIFFS_CHECK_INDEX, SPIFFS_CHECK_PROGRESS, 0, 0);
  res = spiffs_obj_lu_find_entry_visitor(fs, 0, 0, 0, 0, spiffs_object_index_consistency_check_v, 0, &obj_id_log_ix,
        0, 0);
  if (res == SPIFFS_VIS_END) {
    res = SPIFFS_OK;
  }
  if (res != SPIFFS_OK) {
    CHECK_CB(fs, SPIFFS_CHECK_INDEX, SPIFFS_CHECK_ERROR, res, 0);
  }
  CHECK_CB(fs, SPIFFS_CHECK_INDEX, SPIFFS_CHECK_PROGRESS, 256, 0);
  return res;
}
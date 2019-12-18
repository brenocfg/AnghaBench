#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spiffs_span_ix ;
typedef  scalar_t__ spiffs_page_ix ;
typedef  int /*<<< orphan*/  spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
struct TYPE_5__ {int cursor_obj_lu_entry; int /*<<< orphan*/  cursor_block_ix; } ;
typedef  TYPE_1__ spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (scalar_t__) ; 
 scalar_t__ SPIFFS_ERR_NOT_FOUND ; 
 scalar_t__ SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPIFFS_VIS_CHECK_PH ; 
 scalar_t__ SPIFFS_VIS_END ; 
 scalar_t__ spiffs_obj_lu_find_entry_visitor (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  spiffs_obj_lu_find_id_and_span_v ; 

s32_t spiffs_obj_lu_find_id_and_span_by_phdr(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_span_ix spix,
    spiffs_page_ix exclusion_pix,
    spiffs_page_ix *pix) {
  s32_t res;
  spiffs_block_ix bix;
  int entry;

  res = spiffs_obj_lu_find_entry_visitor(fs,
      fs->cursor_block_ix,
      fs->cursor_obj_lu_entry,
      SPIFFS_VIS_CHECK_PH,
      obj_id,
      spiffs_obj_lu_find_id_and_span_v,
      exclusion_pix ? &exclusion_pix : 0,
      &spix,
      &bix,
      &entry);

  if (res == SPIFFS_VIS_END) {
    res = SPIFFS_ERR_NOT_FOUND;
  }

  SPIFFS_CHECK_RES(res);

  if (pix) {
    *pix = SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX(fs, bix, entry);
  }

  fs->cursor_block_ix = bix;
  fs->cursor_obj_lu_entry = entry;

  return res;
}
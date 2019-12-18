#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ spiffs_span_ix ;
typedef  scalar_t__ const spiffs_page_ix ;
struct TYPE_2__ {int obj_id; scalar_t__ span_ix; int flags; } ;
typedef  TYPE_1__ spiffs_page_header ;
typedef  int spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int /*<<< orphan*/ ) ; 
 int SPIFFS_OBJ_ID_IX_FLAG ; 
 scalar_t__ SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_T_OBJ_LU2 ; 
 int /*<<< orphan*/  SPIFFS_PAGE_TO_PADDR (int /*<<< orphan*/ *,scalar_t__ const) ; 
 int SPIFFS_PH_FLAG_DELET ; 
 int SPIFFS_PH_FLAG_FINAL ; 
 int SPIFFS_PH_FLAG_IXDELE ; 
 int SPIFFS_PH_FLAG_USED ; 
 int /*<<< orphan*/  SPIFFS_VIS_COUNTINUE ; 
 int /*<<< orphan*/  _spiffs_rd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32_t spiffs_obj_lu_find_id_and_span_v(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_block_ix bix,
    int ix_entry,
    const void *user_const_p,
    void *user_var_p) {
  s32_t res;
  spiffs_page_header ph;
  spiffs_page_ix pix = SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX(fs, bix, ix_entry);
  res = _spiffs_rd(fs, 0, SPIFFS_OP_T_OBJ_LU2 | SPIFFS_OP_C_READ,
      SPIFFS_PAGE_TO_PADDR(fs, pix), sizeof(spiffs_page_header), (u8_t *)&ph);
  SPIFFS_CHECK_RES(res);
  if (ph.obj_id == obj_id &&
      ph.span_ix == *((spiffs_span_ix*)user_var_p) &&
      (ph.flags & (SPIFFS_PH_FLAG_FINAL | SPIFFS_PH_FLAG_DELET | SPIFFS_PH_FLAG_USED)) == SPIFFS_PH_FLAG_DELET &&
      !((obj_id & SPIFFS_OBJ_ID_IX_FLAG) && (ph.flags & SPIFFS_PH_FLAG_IXDELE) == 0 && ph.span_ix == 0) &&
      (user_const_p == 0 || *((const spiffs_page_ix*)user_const_p) != pix)) {
    return SPIFFS_OK;
  } else {
    return SPIFFS_VIS_COUNTINUE;
  }
}
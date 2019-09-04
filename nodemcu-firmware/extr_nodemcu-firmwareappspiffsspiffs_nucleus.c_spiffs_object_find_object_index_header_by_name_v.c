#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_3__ {scalar_t__ span_ix; int flags; } ;
struct TYPE_4__ {scalar_t__ name; TYPE_1__ p_hdr; } ;
typedef  TYPE_2__ spiffs_page_object_ix_header ;
typedef  int /*<<< orphan*/  spiffs_page_ix ;
typedef  int spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int /*<<< orphan*/ ) ; 
 int SPIFFS_OBJ_ID_DELETED ; 
 int SPIFFS_OBJ_ID_FREE ; 
 int SPIFFS_OBJ_ID_IX_FLAG ; 
 int /*<<< orphan*/  SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_T_OBJ_LU2 ; 
 int /*<<< orphan*/  SPIFFS_PAGE_TO_PADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SPIFFS_PH_FLAG_DELET ; 
 int SPIFFS_PH_FLAG_FINAL ; 
 int SPIFFS_PH_FLAG_IXDELE ; 
 int /*<<< orphan*/  SPIFFS_VIS_COUNTINUE ; 
 int /*<<< orphan*/  _spiffs_rd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static s32_t spiffs_object_find_object_index_header_by_name_v(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_block_ix bix,
    int ix_entry,
    const void *user_const_p,
    void *user_var_p) {
  (void)user_var_p;
  s32_t res;
  spiffs_page_object_ix_header objix_hdr;
  spiffs_page_ix pix = SPIFFS_OBJ_LOOKUP_ENTRY_TO_PIX(fs, bix, ix_entry);
  if (obj_id == SPIFFS_OBJ_ID_FREE || obj_id == SPIFFS_OBJ_ID_DELETED ||
      (obj_id & SPIFFS_OBJ_ID_IX_FLAG) == 0) {
    return SPIFFS_VIS_COUNTINUE;
  }
  res = _spiffs_rd(fs, SPIFFS_OP_T_OBJ_LU2 | SPIFFS_OP_C_READ,
      0, SPIFFS_PAGE_TO_PADDR(fs, pix), sizeof(spiffs_page_object_ix_header), (u8_t *)&objix_hdr);
  SPIFFS_CHECK_RES(res);
  if (objix_hdr.p_hdr.span_ix == 0 &&
      (objix_hdr.p_hdr.flags & (SPIFFS_PH_FLAG_DELET | SPIFFS_PH_FLAG_FINAL | SPIFFS_PH_FLAG_IXDELE)) ==
          (SPIFFS_PH_FLAG_DELET | SPIFFS_PH_FLAG_IXDELE)) {
    if (strcmp((const char*)user_const_p, (char*)objix_hdr.name) == 0) {
      return SPIFFS_OK;
    }
  }

  return SPIFFS_VIS_COUNTINUE;
}
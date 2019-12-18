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
typedef  int u8_t ;
typedef  int /*<<< orphan*/  spiffs_page_ix ;
typedef  int /*<<< orphan*/  spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  scalar_t__ s32_t ;
typedef  int /*<<< orphan*/  flags ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (scalar_t__) ; 
 scalar_t__ SPIFFS_ERR_NOT_FOUND ; 
 scalar_t__ SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_C_UPDT ; 
 int SPIFFS_OP_T_OBJ_LU ; 
 scalar_t__ SPIFFS_PAGE_TO_PADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SPIFFS_PH_FLAG_IXDELE ; 
 scalar_t__ _spiffs_rd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 scalar_t__ _spiffs_wr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int) ; 
 scalar_t__ spiffs_obj_lu_find_id_and_span (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spiffs_page_header ; 

__attribute__((used)) static s32_t spiffs_delete_obj_lazy(spiffs *fs, spiffs_obj_id obj_id) {
  spiffs_page_ix objix_hdr_pix;
  s32_t res;
  res = spiffs_obj_lu_find_id_and_span(fs, obj_id, 0, 0, &objix_hdr_pix);
  if (res == SPIFFS_ERR_NOT_FOUND) {
    return SPIFFS_OK;
  }
  SPIFFS_CHECK_RES(res);
  u8_t flags = 0xff;
#if SPIFFS_NO_BLIND_WRITES
  res = _spiffs_rd(fs, SPIFFS_OP_T_OBJ_LU | SPIFFS_OP_C_READ,
      0, SPIFFS_PAGE_TO_PADDR(fs, objix_hdr_pix) + offsetof(spiffs_page_header, flags),
      sizeof(flags), &flags);
  SPIFFS_CHECK_RES(res);
#endif
  flags &= ~SPIFFS_PH_FLAG_IXDELE;
  res = _spiffs_wr(fs, SPIFFS_OP_T_OBJ_LU | SPIFFS_OP_C_UPDT,
      0, SPIFFS_PAGE_TO_PADDR(fs, objix_hdr_pix) + offsetof(spiffs_page_header, flags),
      sizeof(flags), &flags);
  return res;
}
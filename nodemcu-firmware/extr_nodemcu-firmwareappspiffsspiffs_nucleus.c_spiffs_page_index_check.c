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
typedef  int /*<<< orphan*/  spiffs_span_ix ;
typedef  int spiffs_page_ix ;
typedef  int /*<<< orphan*/  spiffs_fd ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_ERR_INDEX_FREE ; 
 int /*<<< orphan*/  SPIFFS_ERR_INDEX_INVALID ; 
 int /*<<< orphan*/  SPIFFS_ERR_INDEX_LU ; 
 int SPIFFS_MAX_PAGES (int /*<<< orphan*/ *) ; 
 int SPIFFS_OBJ_LOOKUP_PAGES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int SPIFFS_PAGES_PER_BLOCK (int /*<<< orphan*/ *) ; 

__attribute__((used)) static s32_t spiffs_page_index_check(spiffs *fs, spiffs_fd *fd, spiffs_page_ix pix, spiffs_span_ix spix) {
  s32_t res = SPIFFS_OK;
  if (pix == (spiffs_page_ix)-1) {
    // referring to page 0xffff...., bad object index
    return SPIFFS_ERR_INDEX_FREE;
  }
  if (pix % SPIFFS_PAGES_PER_BLOCK(fs) < SPIFFS_OBJ_LOOKUP_PAGES(fs)) {
    // referring to an object lookup page, bad object index
    return SPIFFS_ERR_INDEX_LU;
  }
  if (pix > SPIFFS_MAX_PAGES(fs)) {
    // referring to a bad page
    return SPIFFS_ERR_INDEX_INVALID;
  }
#if SPIFFS_PAGE_CHECK
  spiffs_page_header ph;
  res = _spiffs_rd(
      fs, SPIFFS_OP_T_OBJ_IX | SPIFFS_OP_C_READ,
      fd->file_nbr,
      SPIFFS_PAGE_TO_PADDR(fs, pix),
      sizeof(spiffs_page_header),
      (u8_t *)&ph);
  SPIFFS_CHECK_RES(res);
  SPIFFS_VALIDATE_OBJIX(ph, fd->obj_id, spix);
#endif
  return res;
}
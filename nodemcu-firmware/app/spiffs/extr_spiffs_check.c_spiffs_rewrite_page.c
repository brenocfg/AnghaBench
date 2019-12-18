#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spiffs_page_ix ;
struct TYPE_4__ {int /*<<< orphan*/  obj_id; } ;
typedef  TYPE_1__ spiffs_page_header ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_DATA_PAGE_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ SPIFFS_PAGE_TO_PADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spiffs_page_allocate_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spiffs_phys_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32_t spiffs_rewrite_page(spiffs *fs, spiffs_page_ix cur_pix, spiffs_page_header *p_hdr, spiffs_page_ix *new_pix) {
  s32_t res;
  res = spiffs_page_allocate_data(fs, p_hdr->obj_id, p_hdr, 0,0,0,0, new_pix);
  SPIFFS_CHECK_RES(res);
  res = spiffs_phys_cpy(fs, 0,
      SPIFFS_PAGE_TO_PADDR(fs, *new_pix) + sizeof(spiffs_page_header),
      SPIFFS_PAGE_TO_PADDR(fs, cur_pix) + sizeof(spiffs_page_header),
      SPIFFS_DATA_PAGE_SIZE(fs));
  SPIFFS_CHECK_RES(res);
  return res;
}
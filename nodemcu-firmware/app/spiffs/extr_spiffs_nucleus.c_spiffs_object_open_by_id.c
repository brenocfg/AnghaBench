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
typedef  int /*<<< orphan*/  spiffs_page_ix ;
typedef  int spiffs_obj_id ;
typedef  int /*<<< orphan*/  spiffs_mode ;
typedef  int /*<<< orphan*/  spiffs_flags ;
typedef  int /*<<< orphan*/  spiffs_fd ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int /*<<< orphan*/ ) ; 
 int SPIFFS_OBJ_ID_IX_FLAG ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int /*<<< orphan*/  spiffs_obj_lu_find_id_and_span (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spiffs_object_open_by_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32_t spiffs_object_open_by_id(
    spiffs *fs,
    spiffs_obj_id obj_id,
    spiffs_fd *fd,
    spiffs_flags flags,
    spiffs_mode mode) {
  s32_t res = SPIFFS_OK;
  spiffs_page_ix pix;

  res = spiffs_obj_lu_find_id_and_span(fs, obj_id | SPIFFS_OBJ_ID_IX_FLAG, 0, 0, &pix);
  SPIFFS_CHECK_RES(res);

  res = spiffs_object_open_by_page(fs, pix, fd, flags, mode);

  return res;
}
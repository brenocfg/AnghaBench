#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
struct TYPE_15__ {int /*<<< orphan*/  span_ix; } ;
struct TYPE_12__ {scalar_t__ size; TYPE_9__ p_hdr; int /*<<< orphan*/  meta; scalar_t__ name; } ;
typedef  TYPE_1__ spiffs_page_object_ix_header ;
typedef  int /*<<< orphan*/  spiffs_page_object_ix ;
typedef  int /*<<< orphan*/  spiffs_page_ix ;
typedef  int /*<<< orphan*/  spiffs_obj_id ;
struct TYPE_13__ {int /*<<< orphan*/  objix_hdr_pix; int /*<<< orphan*/  file_nbr; } ;
typedef  TYPE_2__ spiffs_fd ;
struct TYPE_14__ {scalar_t__ work; } ;
typedef  TYPE_3__ spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SPIFFS_CFG_LOG_PAGE_SZ (TYPE_3__*) ; 
 int /*<<< orphan*/  SPIFFS_CHECK_RES (scalar_t__) ; 
 int /*<<< orphan*/  SPIFFS_EV_IX_UPD ; 
 int /*<<< orphan*/  SPIFFS_EV_IX_UPD_HDR ; 
 int /*<<< orphan*/  SPIFFS_OBJ_ID_IX_FLAG ; 
 int /*<<< orphan*/  SPIFFS_OBJ_META_LEN ; 
 int /*<<< orphan*/  SPIFFS_OBJ_NAME_LEN ; 
 scalar_t__ SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_T_OBJ_IX ; 
 int /*<<< orphan*/  SPIFFS_PAGE_TO_PADDR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_VALIDATE_OBJIX (TYPE_9__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SPIFFS_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ _spiffs_rd (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spiffs_cb_object_event (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ spiffs_page_move (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int /*<<< orphan*/ ) ; 

s32_t spiffs_object_update_index_hdr(
    spiffs *fs,
    spiffs_fd *fd,
    spiffs_obj_id obj_id,
    spiffs_page_ix objix_hdr_pix,
    u8_t *new_objix_hdr_data,
    const u8_t name[],
    const u8_t meta[],
    u32_t size,
    spiffs_page_ix *new_pix) {
  s32_t res = SPIFFS_OK;
  spiffs_page_object_ix_header *objix_hdr;
  spiffs_page_ix new_objix_hdr_pix;

  obj_id |=  SPIFFS_OBJ_ID_IX_FLAG;

  if (new_objix_hdr_data) {
    // object index header page already given to us, no need to load it
    objix_hdr = (spiffs_page_object_ix_header *)new_objix_hdr_data;
  } else {
    // read object index header page
    res = _spiffs_rd(fs, SPIFFS_OP_T_OBJ_IX | SPIFFS_OP_C_READ,
        fd->file_nbr, SPIFFS_PAGE_TO_PADDR(fs, objix_hdr_pix), SPIFFS_CFG_LOG_PAGE_SZ(fs), fs->work);
    SPIFFS_CHECK_RES(res);
    objix_hdr = (spiffs_page_object_ix_header *)fs->work;
  }

  SPIFFS_VALIDATE_OBJIX(objix_hdr->p_hdr, obj_id, 0);

  // change name
  if (name) {
    strncpy((char*)objix_hdr->name, (const char*)name, SPIFFS_OBJ_NAME_LEN);
  }
#if SPIFFS_OBJ_META_LEN
  if (meta) {
    _SPIFFS_MEMCPY(objix_hdr->meta, meta, SPIFFS_OBJ_META_LEN);
  }
#else
  (void) meta;
#endif
  if (size) {
    objix_hdr->size = size;
  }

  // move and update page
  res = spiffs_page_move(fs, fd == 0 ? 0 : fd->file_nbr, (u8_t*)objix_hdr, obj_id, 0, objix_hdr_pix, &new_objix_hdr_pix);

  if (res == SPIFFS_OK) {
    if (new_pix) {
      *new_pix = new_objix_hdr_pix;
    }
    // callback on object index update
    spiffs_cb_object_event(fs, (spiffs_page_object_ix *)objix_hdr,
        new_objix_hdr_data ? SPIFFS_EV_IX_UPD : SPIFFS_EV_IX_UPD_HDR,
            obj_id, objix_hdr->p_hdr.span_ix, new_objix_hdr_pix, objix_hdr->size);
    if (fd) fd->objix_hdr_pix = new_objix_hdr_pix; // if this is not in the registered cluster
  }

  return res;
}
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
typedef  int /*<<< orphan*/  u8_t ;
typedef  scalar_t__ u32_t ;
typedef  int /*<<< orphan*/  spiffs_file ;
typedef  int /*<<< orphan*/  spiffs ;
typedef  int /*<<< orphan*/  s32_t ;

/* Variables and functions */
 scalar_t__ MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  SPIFFS_CHECK_RES (int /*<<< orphan*/ ) ; 
 int SPIFFS_COPY_BUFFER_STACK ; 
 int /*<<< orphan*/  SPIFFS_OK ; 
 int SPIFFS_OP_C_MOVD ; 
 int SPIFFS_OP_C_MOVS ; 
 int SPIFFS_OP_T_OBJ_DA ; 
 int /*<<< orphan*/  _spiffs_rd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _spiffs_wr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

s32_t spiffs_phys_cpy(
    spiffs *fs,
    spiffs_file fh,
    u32_t dst,
    u32_t src,
    u32_t len) {
  (void)fh;
  s32_t res;
  u8_t b[SPIFFS_COPY_BUFFER_STACK];
  while (len > 0) {
    u32_t chunk_size = MIN(SPIFFS_COPY_BUFFER_STACK, len);
    res = _spiffs_rd(fs, SPIFFS_OP_T_OBJ_DA | SPIFFS_OP_C_MOVS, fh, src, chunk_size, b);
    SPIFFS_CHECK_RES(res);
    res = _spiffs_wr(fs, SPIFFS_OP_T_OBJ_DA | SPIFFS_OP_C_MOVD,  fh, dst, chunk_size, b);
    SPIFFS_CHECK_RES(res);
    len -= chunk_size;
    src += chunk_size;
    dst += chunk_size;
  }
  return SPIFFS_OK;
}
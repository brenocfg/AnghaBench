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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct stlink_libusb {int /*<<< orphan*/  cmd_len; } ;
struct TYPE_4__ {unsigned char* q_buf; unsigned char* c_buf; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_TO_DEV ; 
 unsigned char STLINK_DEBUG_COMMAND ; 
 unsigned char STLINK_DEBUG_WRITEMEM_8BIT ; 
 int fill_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int send_only (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uint16 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uint32 (unsigned char*,int /*<<< orphan*/ ) ; 

int _stlink_usb_write_mem8(stlink_t *sl, uint32_t addr, uint16_t len) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const data = sl->q_buf;
  unsigned char *const cmd = sl->c_buf;
  int i, ret;

  i = fill_command(sl, SG_DXFER_TO_DEV, 0);
  cmd[i++] = STLINK_DEBUG_COMMAND;
  cmd[i++] = STLINK_DEBUG_WRITEMEM_8BIT;
  write_uint32(&cmd[i], addr);
  write_uint16(&cmd[i + 4], len);
  ret = send_only(slu, 0, cmd, slu->cmd_len);
  if (ret == -1) return ret;

  ret = send_only(slu, 1, data, len);
  if (ret == -1) return ret;

  return 0;
}
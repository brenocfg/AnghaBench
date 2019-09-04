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
struct TYPE_4__ {unsigned char* q_buf; unsigned char* c_buf; int q_len; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 unsigned char STLINK_DEBUG_COMMAND ; 
 unsigned char STLINK_DEBUG_READMEM_32BIT ; 
 int fill_command (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int send_recv (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ,unsigned char* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uint16 (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_uint32 (unsigned char*,int /*<<< orphan*/ ) ; 

int _stlink_usb_read_mem32(stlink_t *sl, uint32_t addr, uint16_t len) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const data = sl->q_buf;
  unsigned char *const cmd = sl->c_buf;
  ssize_t size;
  int i = fill_command(sl, SG_DXFER_FROM_DEV, len);

  cmd[i++] = STLINK_DEBUG_COMMAND;
  cmd[i++] = STLINK_DEBUG_READMEM_32BIT;
  write_uint32(&cmd[i], addr);
  write_uint16(&cmd[i + 4], len);

  size = send_recv(slu, 1, cmd, slu->cmd_len, data, len);
  if (size == -1) {
    printf("[!] send_recv STLINK_DEBUG_READMEM_32BIT\n");
    return (int) size;
  }

  sl->q_len = (int) size;

  return 0;
}
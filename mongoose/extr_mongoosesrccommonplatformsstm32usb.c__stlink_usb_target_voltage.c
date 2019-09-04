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
typedef  int uint32_t ;
struct stlink_libusb {int /*<<< orphan*/  cmd_len; } ;
struct TYPE_4__ {unsigned char* q_buf; unsigned char* c_buf; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int ssize_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 unsigned char STLINK_GET_TARGET_VOLTAGE ; 
 int fill_command (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int send_recv (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ,unsigned char* const,int) ; 

int32_t _stlink_usb_target_voltage(stlink_t *sl) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const rdata = sl->q_buf;
  unsigned char *const cmd = sl->c_buf;
  ssize_t size;
  uint32_t rep_len = 8;
  int i = fill_command(sl, SG_DXFER_FROM_DEV, rep_len);
  uint32_t factor, reading;
  int voltage;

  cmd[i++] = STLINK_GET_TARGET_VOLTAGE;

  size = send_recv(slu, 1, cmd, slu->cmd_len, rdata, rep_len);
  if (size == -1) {
    printf("[!] send_recv STLINK_GET_TARGET_VOLTAGE\n");
    return -1;
  } else if (size != 8) {
    printf("[!] wrong length STLINK_GET_TARGET_VOLTAGE\n");
    return -1;
  }

  factor =
      (rdata[3] << 24) | (rdata[2] << 16) | (rdata[1] << 8) | (rdata[0] << 0);
  reading =
      (rdata[7] << 24) | (rdata[6] << 16) | (rdata[5] << 8) | (rdata[4] << 0);
  voltage = 2400 * reading / factor;

  return voltage;
}
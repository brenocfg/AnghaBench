#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct stlink_libusb {int /*<<< orphan*/  cmd_len; } ;
struct TYPE_5__ {int stlink_v; int jtag_v; } ;
struct TYPE_6__ {unsigned char* q_buf; unsigned char* c_buf; TYPE_1__ version; struct stlink_libusb* backend_data; } ;
typedef  TYPE_2__ stlink_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 unsigned char STLINK_DEBUG_APIV2_SWD_SET_FREQ ; 
 unsigned char STLINK_DEBUG_COMMAND ; 
 int fill_command (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int send_recv (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ,unsigned char* const,int) ; 

int _stlink_usb_set_swdclk(stlink_t *sl, uint16_t clk_divisor) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const data = sl->q_buf;
  unsigned char *const cmd = sl->c_buf;
  ssize_t size;
  int rep_len = 2;
  int i;

  // clock speed only supported by stlink/v2 and for firmware >= 22
  if (sl->version.stlink_v >= 2 && sl->version.jtag_v >= 22) {
    i = fill_command(sl, SG_DXFER_FROM_DEV, rep_len);

    cmd[i++] = STLINK_DEBUG_COMMAND;
    cmd[i++] = STLINK_DEBUG_APIV2_SWD_SET_FREQ;
    cmd[i++] = clk_divisor & 0xFF;
    cmd[i++] = (clk_divisor >> 8) & 0xFF;

    size = send_recv(slu, 1, cmd, slu->cmd_len, data, rep_len);
    if (size == -1) {
      printf("[!] send_recv STLINK_DEBUG_APIV2_SWD_SET_FREQ\n");
      return (int) size;
    }

    return 0;
  } else {
    return -1;
  }
}
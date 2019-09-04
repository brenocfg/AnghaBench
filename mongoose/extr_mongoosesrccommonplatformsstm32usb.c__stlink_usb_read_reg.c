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
typedef  unsigned char uint8_t ;
typedef  void* uint32_t ;
struct stlink_reg {void** r; void* rw2; void* rw; void* process_sp; void* main_sp; void* xpsr; } ;
struct stlink_libusb {int /*<<< orphan*/  cmd_len; } ;
struct TYPE_4__ {unsigned char* q_buf; unsigned char* c_buf; int q_len; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 unsigned char STLINK_DEBUG_COMMAND ; 
 unsigned char STLINK_DEBUG_READREG ; 
 int fill_command (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 void* read_uint32 (unsigned char*,int /*<<< orphan*/ ) ; 
 int send_recv (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ,unsigned char* const,void*) ; 

int _stlink_usb_read_reg(stlink_t *sl, int r_idx, struct stlink_reg *regp) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const data = sl->q_buf;
  unsigned char *const cmd = sl->c_buf;
  ssize_t size;
  uint32_t r;
  uint32_t rep_len = 4;
  int i = fill_command(sl, SG_DXFER_FROM_DEV, rep_len);

  cmd[i++] = STLINK_DEBUG_COMMAND;
  cmd[i++] = STLINK_DEBUG_READREG;
  cmd[i++] = (uint8_t) r_idx;
  size = send_recv(slu, 1, cmd, slu->cmd_len, data, rep_len);
  if (size == -1) {
    printf("[!] send_recv STLINK_DEBUG_READREG\n");
    return (int) size;
  }
  sl->q_len = (int) size;
  r = read_uint32(sl->q_buf, 0);

  switch (r_idx) {
    case 16:
      regp->xpsr = r;
      break;
    case 17:
      regp->main_sp = r;
      break;
    case 18:
      regp->process_sp = r;
      break;
    case 19:
      regp->rw = r; /* XXX ?(primask, basemask etc.) */
      break;
    case 20:
      regp->rw2 = r; /* XXX ?(primask, basemask etc.) */
      break;
    default:
      regp->r[r_idx] = r;
  }

  return 0;
}
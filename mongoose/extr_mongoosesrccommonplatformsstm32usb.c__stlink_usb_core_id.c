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
struct stlink_libusb {int /*<<< orphan*/  cmd_len; } ;
struct TYPE_4__ {unsigned char* c_buf; unsigned char* q_buf; int /*<<< orphan*/  core_id; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SG_DXFER_FROM_DEV ; 
 unsigned char STLINK_DEBUG_COMMAND ; 
 unsigned char STLINK_DEBUG_READCOREID ; 
 int fill_command (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_uint32 (unsigned char* const,int /*<<< orphan*/ ) ; 
 int send_recv (struct stlink_libusb* const,int,unsigned char* const,int /*<<< orphan*/ ,unsigned char* const,int) ; 

int _stlink_usb_core_id(stlink_t *sl) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const cmd = sl->c_buf;
  unsigned char *const data = sl->q_buf;
  ssize_t size;
  int rep_len = 4;
  int i = fill_command(sl, SG_DXFER_FROM_DEV, rep_len);

  cmd[i++] = STLINK_DEBUG_COMMAND;
  cmd[i++] = STLINK_DEBUG_READCOREID;

  size = send_recv(slu, 1, cmd, slu->cmd_len, data, rep_len);
  if (size == -1) {
    printf("[!] send_recv STLINK_DEBUG_READCOREID\n");
    return -1;
  }

  sl->core_id = read_uint32(data, 0);
  return 0;
}
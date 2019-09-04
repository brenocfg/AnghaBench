#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct stlink_libusb {int protocoll; int /*<<< orphan*/  sg_transfer_idx; } ;
struct TYPE_3__ {unsigned char* c_buf; struct stlink_libusb* backend_data; } ;
typedef  TYPE_1__ stlink_t ;
typedef  enum SCSI_Generic_Direction { ____Placeholder_SCSI_Generic_Direction } SCSI_Generic_Direction ;

/* Variables and functions */
 int SG_DXFER_FROM_DEV ; 
 int /*<<< orphan*/  memset (unsigned char* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_uint32 (unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fill_command(stlink_t *sl, enum SCSI_Generic_Direction dir,
                        uint32_t len) {
  struct stlink_libusb *const slu = sl->backend_data;
  unsigned char *const cmd = sl->c_buf;
  int i = 0;
  memset(cmd, 0, sizeof(sl->c_buf));
  if (slu->protocoll == 1) {
    cmd[i++] = 'U';
    cmd[i++] = 'S';
    cmd[i++] = 'B';
    cmd[i++] = 'C';
    write_uint32(&cmd[i], slu->sg_transfer_idx);
    write_uint32(&cmd[i + 4], len);
    i += 8;
    cmd[i++] = (dir == SG_DXFER_FROM_DEV) ? 0x80 : 0;
    cmd[i++] = 0;   /* Logical unit */
    cmd[i++] = 0xa; /* Command length */
  }
  return i;
}
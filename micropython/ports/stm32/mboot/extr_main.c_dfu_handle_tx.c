#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int cmd; int status; scalar_t__ addr; } ;

/* Variables and functions */
#define  DFU_CMD_DNLOAD 131 
#define  DFU_CMD_EXIT 130 
#define  DFU_CMD_NONE 129 
#define  DFU_CMD_UPLOAD 128 
 int DFU_GETSTATUS ; 
 int DFU_STATUS_BUSY ; 
 int DFU_STATUS_MANIFEST ; 
 int DFU_STATUS_UPLOAD_IDLE ; 
 int DFU_UPLOAD ; 
 TYPE_1__ dfu_state ; 
 int /*<<< orphan*/  do_read (scalar_t__,int,int*) ; 

__attribute__((used)) static int dfu_handle_tx(int cmd, int arg, int len, uint8_t *buf, int max_len) {
    if (cmd == DFU_UPLOAD) {
        if (arg >= 2) {
            dfu_state.cmd = DFU_CMD_UPLOAD;
            uint32_t addr = (arg - 2) * max_len + dfu_state.addr;
            do_read(addr, len, buf);
            return len;
        }
    } else if (cmd == DFU_GETSTATUS && len == 6) {
        // execute command and get status
        switch (dfu_state.cmd) {
            case DFU_CMD_NONE:
                break;
            case DFU_CMD_EXIT:
                dfu_state.status = DFU_STATUS_MANIFEST;
                break;
            case DFU_CMD_UPLOAD:
                dfu_state.status = DFU_STATUS_UPLOAD_IDLE;
                break;
            case DFU_CMD_DNLOAD:
                dfu_state.status = DFU_STATUS_BUSY;
                break;
        }
        buf[0] = 0;
        buf[1] = dfu_state.cmd; // TODO is this correct?
        buf[2] = 0;
        buf[3] = 0;
        buf[4] = dfu_state.status;
        buf[5] = 0;
        return 6;
    }
    return -1;
}
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
struct TYPE_2__ {int wBlockNum; int wLength; int /*<<< orphan*/  buf; void* cmd; void* status; } ;

/* Variables and functions */
 int DFU_ABORT ; 
 int DFU_CLRSTATUS ; 
 void* DFU_CMD_DNLOAD ; 
 void* DFU_CMD_EXIT ; 
 void* DFU_CMD_NONE ; 
 int DFU_DNLOAD ; 
 void* DFU_STATUS_IDLE ; 
 TYPE_1__ dfu_state ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static void dfu_handle_rx(int cmd, int arg, int len, const void *buf) {
    if (cmd == DFU_CLRSTATUS) {
        // clear status
        dfu_state.status = DFU_STATUS_IDLE;
        dfu_state.cmd = DFU_CMD_NONE;
    } else if (cmd == DFU_ABORT) {
        // clear status
        dfu_state.status = DFU_STATUS_IDLE;
        dfu_state.cmd = DFU_CMD_NONE;
    } else if (cmd == DFU_DNLOAD) {
        if (len == 0) {
            // exit DFU
            dfu_state.cmd = DFU_CMD_EXIT;
        } else {
            // download
            dfu_state.cmd = DFU_CMD_DNLOAD;
            dfu_state.wBlockNum = arg;
            dfu_state.wLength = len;
            memcpy(dfu_state.buf, buf, len);
        }
    }
}
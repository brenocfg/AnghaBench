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
struct TYPE_2__ {scalar_t__ status; scalar_t__ cmd; } ;

/* Variables and functions */
 scalar_t__ DFU_CMD_DNLOAD ; 
 scalar_t__ DFU_CMD_NONE ; 
 scalar_t__ DFU_STATUS_BUSY ; 
 scalar_t__ DFU_STATUS_MANIFEST ; 
 scalar_t__ dfu_process_dnload () ; 
 TYPE_1__ dfu_state ; 
 int /*<<< orphan*/  do_reset () ; 

__attribute__((used)) static void dfu_process(void) {
    if (dfu_state.status == DFU_STATUS_MANIFEST) {
        do_reset();
    }

    if (dfu_state.status == DFU_STATUS_BUSY) {
        if (dfu_state.cmd == DFU_CMD_DNLOAD) {
            dfu_state.cmd = DFU_CMD_NONE;
            dfu_state.status = dfu_process_dnload();
        }
    }
}
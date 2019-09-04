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
struct TYPE_2__ {int addr; int /*<<< orphan*/  cmd; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DFU_CMD_NONE ; 
 int /*<<< orphan*/  DFU_STATUS_IDLE ; 
 TYPE_1__ dfu_state ; 

__attribute__((used)) static void dfu_init(void) {
    dfu_state.status = DFU_STATUS_IDLE;
    dfu_state.cmd = DFU_CMD_NONE;
    dfu_state.addr = 0x08000000;
}
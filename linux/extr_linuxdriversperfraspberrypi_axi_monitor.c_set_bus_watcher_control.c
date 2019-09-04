#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {TYPE_1__* dev; int /*<<< orphan*/  firmware; TYPE_2__* monitor; } ;
struct TYPE_5__ {int /*<<< orphan*/  base_address; scalar_t__ use_mailbox_interface; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPI_FIRMWARE_SET_PERIPH_REG ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ *,char*) ; 
 int rpi_firmware_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_3__* state ; 
 int /*<<< orphan*/  write_reg (int,int,int) ; 

__attribute__((used)) static void set_bus_watcher_control(int monitor, int watcher, u32 set)
{
	if (state->monitor[monitor].use_mailbox_interface) {
		u32 tmp[3] = {(u32)(state->monitor[monitor].base_address +
				    watcher), 1, set};
		int err = rpi_firmware_property(state->firmware,
						RPI_FIRMWARE_SET_PERIPH_REG,
						tmp, sizeof(tmp));
		if (err < 0 || tmp[1] != 1)
			dev_err_once(&state->dev->dev,
				"Failed to set bus watcher control");
	} else
		write_reg(monitor, watcher, set);
}
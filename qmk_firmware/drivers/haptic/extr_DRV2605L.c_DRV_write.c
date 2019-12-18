#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int DRV2605L_BASE_ADDRESS ; 
 int /*<<< orphan*/ * DRV2605L_transfer_buffer ; 
 int /*<<< orphan*/  i2c_transmit (int,int /*<<< orphan*/ *,int,int) ; 

void DRV_write(uint8_t drv_register, uint8_t settings) {
    DRV2605L_transfer_buffer[0] = drv_register;
    DRV2605L_transfer_buffer[1] = settings;
    i2c_transmit(DRV2605L_BASE_ADDRESS << 1, DRV2605L_transfer_buffer, 2, 100);
}
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
 int I2C_ADDRESS_SA0_1 ; 
 int /*<<< orphan*/  I2C_COMMAND ; 
 int /*<<< orphan*/  i2c_transmit (int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * micro_oled_transfer_buffer ; 

void send_command(uint8_t command) {
    micro_oled_transfer_buffer[0] = I2C_COMMAND;
    micro_oled_transfer_buffer[1] = command;
    i2c_transmit(I2C_ADDRESS_SA0_1 << 1, micro_oled_transfer_buffer, 2, 100);
}
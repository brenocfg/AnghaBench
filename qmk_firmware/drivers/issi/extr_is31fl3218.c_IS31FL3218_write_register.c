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
 int /*<<< orphan*/  ISSI_ADDRESS ; 
 int /*<<< orphan*/  ISSI_TIMEOUT ; 
 int /*<<< orphan*/ * g_twi_transfer_buffer ; 
 int /*<<< orphan*/  i2c_transmit (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void IS31FL3218_write_register(uint8_t reg, uint8_t data) {
    g_twi_transfer_buffer[0] = reg;
    g_twi_transfer_buffer[1] = data;
    i2c_transmit(ISSI_ADDRESS, g_twi_transfer_buffer, 2, ISSI_TIMEOUT);
}
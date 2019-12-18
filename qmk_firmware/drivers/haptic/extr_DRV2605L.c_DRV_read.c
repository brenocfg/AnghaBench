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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int DRV2605L_BASE_ADDRESS ; 
 scalar_t__* DRV2605L_read_buffer ; 
 scalar_t__ DRV2605L_read_register ; 
 scalar_t__* DRV2605L_tx_register ; 
 scalar_t__ MSG_OK ; 
 int /*<<< orphan*/  i2c_readReg (int,scalar_t__,scalar_t__*,int,int) ; 
 scalar_t__ i2c_transmit_receive (int,scalar_t__*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

uint8_t DRV_read(uint8_t regaddress) {
#ifdef __AVR__
    i2c_readReg(DRV2605L_BASE_ADDRESS << 1, regaddress, DRV2605L_read_buffer, 1, 100);
    DRV2605L_read_register = (uint8_t)DRV2605L_read_buffer[0];
#else
    DRV2605L_tx_register[0] = regaddress;
    if (MSG_OK != i2c_transmit_receive(DRV2605L_BASE_ADDRESS << 1, DRV2605L_tx_register, 1, DRV2605L_read_buffer, 1)) {
        printf("err reading reg \n");
    }
    DRV2605L_read_register = (uint8_t)DRV2605L_read_buffer[0];
#endif
    return DRV2605L_read_register;
}
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
typedef  scalar_t__ i2c_status_t ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 scalar_t__ CMD_INPUT_0 ; 
 scalar_t__ CMD_INPUT_1 ; 
 scalar_t__ I2C_STATUS_SUCCESS ; 
 scalar_t__ SLAVE_TO_ADDR (scalar_t__) ; 
 int /*<<< orphan*/  TIMEOUT ; 
 scalar_t__ i2c_readReg (scalar_t__,scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print (char*) ; 

uint8_t pca9555_readPins(uint8_t slave_addr, uint8_t port) {
    uint8_t addr = SLAVE_TO_ADDR(slave_addr);
    uint8_t cmd  = port ? CMD_INPUT_1 : CMD_INPUT_0;

    uint8_t      data = 0;
    i2c_status_t ret  = i2c_readReg(addr, cmd, &data, sizeof(data), TIMEOUT);
    if (ret != I2C_STATUS_SUCCESS) {
        print("pca9555_readPins::FAILED\n");
    }
    return data;
}
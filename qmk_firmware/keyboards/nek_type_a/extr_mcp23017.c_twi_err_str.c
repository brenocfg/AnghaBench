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
typedef  int uint8_t ;

/* Variables and functions */
#define  TWI_ERROR_BusCaptureTimeout 133 
#define  TWI_ERROR_BusFault 132 
#define  TWI_ERROR_NoError 131 
#define  TWI_ERROR_SlaveNAK 130 
#define  TWI_ERROR_SlaveNotReady 129 
#define  TWI_ERROR_SlaveResponseTimeout 128 

__attribute__((used)) static const char *twi_err_str(uint8_t res) {
    switch (res) {
        case TWI_ERROR_NoError:
            return "OK";
        case TWI_ERROR_BusFault:
            return "BUSFAULT";
        case TWI_ERROR_BusCaptureTimeout:
            return "BUSTIMEOUT";
        case TWI_ERROR_SlaveResponseTimeout:
            return "SLAVETIMEOUT";
        case TWI_ERROR_SlaveNotReady:
            return "SLAVENOTREADY";
        case TWI_ERROR_SlaveNAK:
            return "SLAVENAK";
        default:
            return "UNKNOWN";
    }
}
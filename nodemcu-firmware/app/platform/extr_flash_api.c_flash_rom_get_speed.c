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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */
#define  SPEED_20MHZ 131 
#define  SPEED_26MHZ 130 
#define  SPEED_40MHZ 129 
#define  SPEED_80MHZ 128 
 TYPE_1__* flash_rom_getinfo () ; 

uint32_t flash_rom_get_speed(void)
{
    uint32_t speed = 0;
    uint8_t spi_speed = flash_rom_getinfo()->speed;
    switch (spi_speed)
    {
    case SPEED_40MHZ:
        // 40MHz
        speed = 40000000;
        break;
    case SPEED_26MHZ:
        //26.7MHz
        speed = 26700000;
        break;
    case SPEED_20MHZ:
        // 20MHz
        speed = 20000000;
        break;
    case SPEED_80MHZ:
        //80MHz
        speed = 80000000;
        break;
    }
    return speed;
}
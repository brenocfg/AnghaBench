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
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
#define  MODE_DIO 131 
#define  MODE_DOUT 130 
#define  MODE_QIO 129 
#define  MODE_QOUT 128 
 TYPE_1__* flash_rom_getinfo () ; 

uint8_t flash_rom_get_mode(void)
{
    uint8_t mode = flash_rom_getinfo()->mode;
    switch (mode)
    {
    // Reserved for future use
    case MODE_QIO:
        break;
    case MODE_QOUT:
        break;
    case MODE_DIO:
        break;
    case MODE_DOUT:
        break;
    }
    return mode;
}
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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
#define  SIZE_128MBIT 137 
#define  SIZE_16MBIT 136 
#define  SIZE_16MBIT_8M_8M 135 
#define  SIZE_2MBIT 134 
#define  SIZE_32MBIT 133 
#define  SIZE_32MBIT_16M_16M 132 
#define  SIZE_32MBIT_8M_8M 131 
#define  SIZE_4MBIT 130 
#define  SIZE_64MBIT 129 
#define  SIZE_8MBIT 128 
 TYPE_1__* flash_rom_getinfo () ; 

uint32_t flash_rom_get_size_byte(void)
{
    static uint32_t flash_size = 0;
    if (flash_size == 0)
    {
        switch (flash_rom_getinfo()->size)
        {
        case SIZE_2MBIT:
            // 2Mbit, 256kByte
            flash_size = 256 * 1024;
            break;
        case SIZE_4MBIT:
            // 4Mbit, 512kByte
            flash_size = 512 * 1024;
            break;
        case SIZE_8MBIT:
            // 8Mbit, 1MByte
            flash_size = 1 * 1024 * 1024;
            break;
        case SIZE_16MBIT:
            // 16Mbit, 2MByte
            flash_size = 2 * 1024 * 1024;
            break;
        case SIZE_32MBIT:
            // 32Mbit, 4MByte
            flash_size = 4 * 1024 * 1024;
            break;
        case SIZE_16MBIT_8M_8M:
            // 16Mbit, 2MByte
            flash_size = 2 * 1024 * 1024;
            break;
        case SIZE_32MBIT_8M_8M:
            // 32Mbit, 4MByte
            flash_size = 4 * 1024 * 1024;
            break;
        case SIZE_32MBIT_16M_16M:
            // 32Mbit, 4MByte
            flash_size = 4 * 1024 * 1024;
            break;
        case SIZE_64MBIT:
            // 64Mbit, 8MByte
            flash_size = 8 * 1024 * 1024;
            break;
        case SIZE_128MBIT:
            // 128Mbit, 16MByte
            flash_size = 16 * 1024 * 1024;
            break;
        default:
            // Unknown flash size, fall back mode.
            flash_size = 512 * 1024;
            break;
        }
    }
    return flash_size;
}
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
typedef  int uint32_t ;

/* Variables and functions */
 int SIZE_128MBIT ; 
 int SIZE_16MBIT ; 
 int SIZE_2MBIT ; 
 int SIZE_32MBIT ; 
 int SIZE_4MBIT ; 
 int SIZE_64MBIT ; 
 int SIZE_8MBIT ; 
 int /*<<< orphan*/  flash_rom_set_size_type (int) ; 

bool flash_rom_set_size_byte(uint32_t size)
{
    // Dangerous, here are dinosaur infested!!!!!
    // Reboot required!!!
    // If you don't know what you're doing, your nodemcu may turn into stone ...
    bool result = true;
    uint32_t flash_size = 0;
    switch (size)
    {
    case 256 * 1024:
        // 2Mbit, 256kByte
        flash_size = SIZE_2MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 512 * 1024:
        // 4Mbit, 512kByte
        flash_size = SIZE_4MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 1 * 1024 * 1024:
        // 8Mbit, 1MByte
        flash_size = SIZE_8MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 2 * 1024 * 1024:
        // 16Mbit, 2MByte
        flash_size = SIZE_16MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 4 * 1024 * 1024:
        // 32Mbit, 4MByte
        flash_size = SIZE_32MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 8 * 1024 * 1024:
        // 64Mbit, 8MByte
        flash_size = SIZE_64MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    case 16 * 1024 * 1024:
        // 128Mbit, 16MByte
        flash_size = SIZE_128MBIT;
        flash_rom_set_size_type(flash_size);
        break;
    default:
        // Unknown flash size.
        result = false;
        break;
    }
    return result;
}
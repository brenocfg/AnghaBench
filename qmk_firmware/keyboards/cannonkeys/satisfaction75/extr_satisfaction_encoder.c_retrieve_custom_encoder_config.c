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
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ DYNAMIC_KEYMAP_CUSTOM_ENCODER ; 
 int eeprom_read_byte (void*) ; 

uint16_t retrieve_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(DYNAMIC_KEYMAP_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    //big endian
    uint16_t keycode = eeprom_read_byte(addr) << 8;
    keycode |= eeprom_read_byte(addr + 1);
    return keycode;
#else
    return 0;
#endif
}
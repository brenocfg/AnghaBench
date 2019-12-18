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
 int /*<<< orphan*/  eeprom_update_byte (void*,int) ; 

void set_custom_encoder_config(uint8_t encoder_idx, uint8_t behavior, uint16_t new_code){
#ifdef DYNAMIC_KEYMAP_ENABLE
    void* addr = (void*)(DYNAMIC_KEYMAP_CUSTOM_ENCODER + (encoder_idx * 6) + (behavior * 2));
    eeprom_update_byte(addr, (uint8_t)(new_code >> 8));
    eeprom_update_byte(addr + 1, (uint8_t)(new_code & 0xFF));
#endif
}
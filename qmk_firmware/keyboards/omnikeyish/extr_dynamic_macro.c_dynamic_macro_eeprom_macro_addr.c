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
typedef  int /*<<< orphan*/  dynamic_macro_t ;

/* Variables and functions */
 void* DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR ; 

inline void* dynamic_macro_eeprom_macro_addr(uint8_t macro_id) { 
    return DYNAMIC_MACRO_EEPROM_BLOCK0_ADDR + sizeof(dynamic_macro_t) * macro_id;
}
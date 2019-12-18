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

/* Variables and functions */
 int /*<<< orphan*/  EECONFIG_HANDEDNESS ; 
 int /*<<< orphan*/  SPLIT_HAND_PIN ; 
 int eeprom_read_byte (int /*<<< orphan*/ ) ; 
 int is_keyboard_master () ; 
 int /*<<< orphan*/  readPin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinInput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setPinInputHigh (int /*<<< orphan*/ ) ; 

bool is_keyboard_left(void) {
    #if defined(MASTER_LEFT)
        return is_keyboard_master();
    #elif defined(MASTER_RIGHT)
        return !is_keyboard_master();
    #elif defined(SPLIT_HAND_PIN)
        // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
        setPinInputHigh(SPLIT_HAND_PIN);
        bool x = !readPin(SPLIT_HAND_PIN);
        setPinInput(SPLIT_HAND_PIN);
        return x;
    #elif defined(EE_HANDS)
        return eeprom_read_byte(EECONFIG_HANDEDNESS);
    #endif

    return is_keyboard_master();
}
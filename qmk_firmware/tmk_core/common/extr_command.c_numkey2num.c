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
#define  KC_0 137 
#define  KC_1 136 
#define  KC_2 135 
#define  KC_3 134 
#define  KC_4 133 
#define  KC_5 132 
#define  KC_6 131 
#define  KC_7 130 
#define  KC_8 129 
#define  KC_9 128 

uint8_t numkey2num(uint8_t code) {
    switch (code) {
        case KC_1:
            return 1;
        case KC_2:
            return 2;
        case KC_3:
            return 3;
        case KC_4:
            return 4;
        case KC_5:
            return 5;
        case KC_6:
            return 6;
        case KC_7:
            return 7;
        case KC_8:
            return 8;
        case KC_9:
            return 9;
        case KC_0:
            return 0;
    }
    return 0;
}
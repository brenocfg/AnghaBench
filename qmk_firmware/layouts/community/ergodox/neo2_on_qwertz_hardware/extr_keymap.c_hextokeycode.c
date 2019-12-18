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
 int KC_A ; 
 int KC_P0 ; 
 int KC_P1 ; 

uint16_t hextokeycode(uint8_t hex) {
    if (hex == 0x0) {
        return KC_P0;
    }
    if (hex < 0xA) {
        return KC_P1 + (hex - 0x1);
    }
    return KC_A + (hex - 0xA);
}
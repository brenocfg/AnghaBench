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
typedef  int uint16_t ;

/* Variables and functions */
#define  BK_LWER 133 
#define  DL_RAIS 132 
#define  ET_RAIS 131 
#define  LOWER 130 
#define  RAISE 129 
#define  SP_LWER 128 

bool music_mask_user(uint16_t keycode) {
    switch (keycode) {
        case RAISE:
        case LOWER:
        case BK_LWER:
        case SP_LWER:
        case DL_RAIS:
        case ET_RAIS:
            return false;
        default:
            return true;
    }
}
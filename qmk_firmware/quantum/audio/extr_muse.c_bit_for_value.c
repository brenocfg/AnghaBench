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
 int /*<<< orphan*/  MUSE_B1 ; 
#define  MUSE_C1 136 
#define  MUSE_C2 135 
#define  MUSE_C3 134 
#define  MUSE_C4 133 
#define  MUSE_C6 132 
#define  MUSE_C8 131 
#define  MUSE_C_1_2 130 
#define  MUSE_OFF 129 
#define  MUSE_ON 128 
 int muse_timer_1bit ; 
 int muse_timer_2bit ; 
 unsigned long muse_timer_31bit ; 
 int muse_timer_4bit ; 

bool bit_for_value(uint8_t value) {
    switch (value) {
        case MUSE_OFF:
            return 0;
        case MUSE_ON:
            return 1;
        case MUSE_C_1_2:
            return muse_timer_1bit;
        case MUSE_C1:
            return (muse_timer_4bit & 1);
        case MUSE_C2:
            return (muse_timer_4bit & 2);
        case MUSE_C4:
            return (muse_timer_4bit & 4);
        case MUSE_C8:
            return (muse_timer_4bit & 8);
        case MUSE_C3:
            return (muse_timer_2bit & 1);
        case MUSE_C6:
            return (muse_timer_2bit & 2);
        default:
            return muse_timer_31bit & (1UL << (value - MUSE_B1));
    }
}
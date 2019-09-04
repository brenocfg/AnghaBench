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
typedef  int mp_int_t ;

/* Variables and functions */
 int MP_SMALL_INT_MAX ; 
 int MP_SMALL_INT_MIN ; 

bool mp_small_int_mul_overflow(mp_int_t x, mp_int_t y) {
    // Check for multiply overflow; see CERT INT32-C
    if (x > 0) { // x is positive
        if (y > 0) { // x and y are positive
            if (x > (MP_SMALL_INT_MAX / y)) {
                return true;
            }
        } else { // x positive, y nonpositive
            if (y < (MP_SMALL_INT_MIN / x)) {
                return true;
            }
        } // x positive, y nonpositive
    } else { // x is nonpositive
        if (y > 0) { // x is nonpositive, y is positive
            if (x < (MP_SMALL_INT_MIN / y)) {
                return true;
            }
        } else { // x and y are nonpositive
            if (x != 0 && y < (MP_SMALL_INT_MAX / x)) {
                return true;
            }
        } // End if x and y are nonpositive
    } // End if x is nonpositive
    return false;
}
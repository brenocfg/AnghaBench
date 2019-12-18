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
 int QK_ONE_SHOT_MOD ; 
 int QK_ONE_SHOT_MOD_MAX ; 

__attribute__((used)) static inline uint16_t translate_keycode(uint16_t keycode) {
    if (keycode > QK_ONE_SHOT_MOD && keycode <= QK_ONE_SHOT_MOD_MAX) {
        return keycode ^ QK_ONE_SHOT_MOD;
    } else {
        return keycode;
    }
}
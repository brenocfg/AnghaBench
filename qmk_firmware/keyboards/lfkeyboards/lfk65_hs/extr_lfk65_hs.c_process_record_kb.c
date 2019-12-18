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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  keyrecord_t ;

/* Variables and functions */
 scalar_t__ RESET ; 
 int process_record_user (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_keyboard_kb () ; 

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ pressed; } ;
struct TYPE_6__ {TYPE_1__ event; } ;
typedef  TYPE_2__ keyrecord_t ;

/* Variables and functions */
 scalar_t__ RESET ; 
 int /*<<< orphan*/  click (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  click_hz ; 
 int /*<<< orphan*/  click_time ; 
 scalar_t__ click_toggle ; 
 int process_record_user (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  reset_keyboard_kb () ; 

bool process_record_kb(uint16_t keycode, keyrecord_t* record)
{
    if (click_toggle && record->event.pressed){
        click(click_hz, click_time);
    }
    if (keycode == RESET) {
        reset_keyboard_kb();
    } else {
    }
    return process_record_user(keycode, record);
}
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
typedef  scalar_t__ visualizer_keyboard_status_t ;
typedef  scalar_t__ systime_t ;
typedef  int /*<<< orphan*/  GSourceListener ;
typedef  int /*<<< orphan*/  GSourceHandle ;

/* Variables and functions */
 scalar_t__ MS2ST (int) ; 
 scalar_t__* begin_write_current_status () ; 
 scalar_t__ chVTGetSystemTimeX () ; 
 scalar_t__ current_status ; 
 int /*<<< orphan*/  end_write_current_status () ; 
 int /*<<< orphan*/ * geventGetSourceListener (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  geventSendEvent (int /*<<< orphan*/ *) ; 

void update_status(bool changed) {
    if (changed) {
        GSourceListener* listener = geventGetSourceListener((GSourceHandle)&current_status, NULL);
        if (listener) {
            geventSendEvent(listener);
        }
    }
#ifdef SERIAL_LINK_ENABLE
    static systime_t last_update    = 0;
    systime_t        current_update = chVTGetSystemTimeX();
    systime_t        delta          = current_update - last_update;
    if (changed || delta > MS2ST(10)) {
        last_update                     = current_update;
        visualizer_keyboard_status_t* r = begin_write_current_status();
        *r                              = current_status;
        end_write_current_status();
    }
#endif
}
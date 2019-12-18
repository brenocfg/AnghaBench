#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mp_uint_t ;
struct TYPE_4__ {int previous_brightness; } ;
typedef  TYPE_1__ microbit_display_obj_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAY_TICKER_SLOT ; 
 int MAX_BRIGHTNESS ; 
 int /*<<< orphan*/  clear_ticker_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  displaySetPinsForRow (TYPE_1__*,int) ; 
 TYPE_1__ microbit_display_obj ; 
 int* render_timings ; 

__attribute__((used)) static int32_t callback(void) {
    microbit_display_obj_t *display = &microbit_display_obj;
    mp_uint_t brightness = display->previous_brightness;
    displaySetPinsForRow(display, brightness);
    brightness += 1;
    if (brightness == MAX_BRIGHTNESS) {
        clear_ticker_callback(DISPLAY_TICKER_SLOT);
        return -1;
    }
    display->previous_brightness = brightness;
    // Return interval (in 16us ticks) until next callback
    return render_timings[brightness];
}
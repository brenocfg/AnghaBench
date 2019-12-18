#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int b; int g; int r; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  apa102_end_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apa102_send_frame (int) ; 
 int /*<<< orphan*/  apa102_start_frame () ; 

void apa102_send_array(uint8_t *data, uint16_t leds) {  // Data is struct of 3 bytes. RGB - leds is number of leds in data
    apa102_start_frame();
    while (leds--) {
        apa102_send_frame(0xFF000000 | (data->b << 16) | (data->g << 8) | data->r);
        data++;
    }
    apa102_end_frame(leds);
}
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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  apa102_send_byte (int) ; 

void apa102_send_frame(uint32_t frame) {
    for (uint32_t i = 0xFF; i > 0;) {
        apa102_send_byte(frame & i);
        i = i << 8;
    }
}
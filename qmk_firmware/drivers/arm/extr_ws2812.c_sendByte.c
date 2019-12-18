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
 int /*<<< orphan*/  RGB_DI_PIN ; 
 int /*<<< orphan*/  T0H ; 
 int /*<<< orphan*/  T0L ; 
 int /*<<< orphan*/  T1H ; 
 int /*<<< orphan*/  T1L ; 
 int /*<<< orphan*/  wait_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writePinLow (int /*<<< orphan*/ ) ; 

void sendByte(uint8_t byte) {
    // WS2812 protocol wants most significant bits first
    for (unsigned char bit = 0; bit < 8; bit++) {
        bool is_one = byte & (1 << (7 - bit));
        // using something like wait_ns(is_one ? T1L : T0L) here throws off timings
        if (is_one) {
            // 1
            writePinHigh(RGB_DI_PIN);
            wait_ns(T1H);
            writePinLow(RGB_DI_PIN);
            wait_ns(T1L);
        } else {
            // 0
            writePinHigh(RGB_DI_PIN);
            wait_ns(T0H);
            writePinLow(RGB_DI_PIN);
            wait_ns(T0L);
        }
    }
}
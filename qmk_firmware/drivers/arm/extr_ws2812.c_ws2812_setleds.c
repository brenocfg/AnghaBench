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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  w; int /*<<< orphan*/  b; int /*<<< orphan*/  r; int /*<<< orphan*/  g; } ;
typedef  TYPE_1__ LED_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  RES ; 
 int /*<<< orphan*/  chSysLock () ; 
 int /*<<< orphan*/  chSysUnlock () ; 
 int /*<<< orphan*/  sendByte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ws2812_init () ; 

void ws2812_setleds(LED_TYPE *ledarray, uint16_t leds) {
    static bool s_init = false;
    if (!s_init) {
        ws2812_init();
        s_init = true;
    }

    // this code is very time dependent, so we need to disable interrupts
    chSysLock();

    for (uint8_t i = 0; i < leds; i++) {
        // WS2812 protocol dictates grb order
        sendByte(ledarray[i].g);
        sendByte(ledarray[i].r);
        sendByte(ledarray[i].b);
#ifdef RGBW
        sendByte(ledarray[i].w);
#endif
    }

    wait_ns(RES);

    chSysUnlock();
}
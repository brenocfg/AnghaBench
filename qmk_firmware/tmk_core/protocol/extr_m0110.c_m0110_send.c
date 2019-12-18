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
 int /*<<< orphan*/  WAIT_MS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WAIT_US (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  clock_hi ; 
 int /*<<< orphan*/  clock_lo ; 
 int /*<<< orphan*/  data_hi () ; 
 int /*<<< orphan*/  data_lo () ; 
 int /*<<< orphan*/  idle () ; 
 scalar_t__ m0110_error ; 
 int /*<<< orphan*/  phex (scalar_t__) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  request () ; 

uint8_t m0110_send(uint8_t data) {
    m0110_error = 0;

    request();
    WAIT_MS(clock_lo, 250, 1);  // keyboard may block long time
    for (uint8_t bit = 0x80; bit; bit >>= 1) {
        WAIT_US(clock_lo, 250, 3);
        if (data & bit) {
            data_hi();
        } else {
            data_lo();
        }
        WAIT_US(clock_hi, 200, 4);
    }
    _delay_us(100);  // hold last bit for 80us
    idle();
    return 1;
ERROR:
    print("m0110_send err: ");
    phex(m0110_error);
    print("\n");
    _delay_ms(500);
    idle();
    return 0;
}
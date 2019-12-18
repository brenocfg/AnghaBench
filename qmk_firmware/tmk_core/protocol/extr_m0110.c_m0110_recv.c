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
 int /*<<< orphan*/  clock_hi ; 
 int /*<<< orphan*/  clock_lo ; 
 scalar_t__ data_in () ; 
 int /*<<< orphan*/  idle () ; 
 scalar_t__ m0110_error ; 
 int /*<<< orphan*/  phex (scalar_t__) ; 
 int /*<<< orphan*/  print (char*) ; 

uint8_t m0110_recv(void) {
    uint8_t data = 0;
    m0110_error  = 0;

    WAIT_MS(clock_lo, 250, 1);  // keyboard may block long time
    for (uint8_t i = 0; i < 8; i++) {
        data <<= 1;
        WAIT_US(clock_lo, 200, 2);
        WAIT_US(clock_hi, 200, 3);
        if (data_in()) {
            data |= 1;
        }
    }
    idle();
    return data;
ERROR:
    print("m0110_recv err: ");
    phex(m0110_error);
    print("\n");
    _delay_ms(500);
    idle();
    return 0xFF;
}
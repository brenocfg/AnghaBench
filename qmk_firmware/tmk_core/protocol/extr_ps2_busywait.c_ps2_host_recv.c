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
 scalar_t__ PS2_ERR_NONE ; 
 scalar_t__ PS2_ERR_PARITY ; 
 scalar_t__ PS2_ERR_STARTBIT3 ; 
 int /*<<< orphan*/  WAIT (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clock_hi ; 
 int /*<<< orphan*/  clock_lo ; 
 int /*<<< orphan*/  data_hi ; 
 int data_in () ; 
 int /*<<< orphan*/  data_lo ; 
 int /*<<< orphan*/  idle () ; 
 int /*<<< orphan*/  inhibit () ; 
 scalar_t__ ps2_error ; 
 int /*<<< orphan*/  xprintf (char*,scalar_t__) ; 

uint8_t ps2_host_recv(void) {
    uint8_t data   = 0;
    bool    parity = true;
    ps2_error      = PS2_ERR_NONE;

    /* release lines(idle state) */
    idle();

    /* start bit [1] */
    WAIT(clock_lo, 100, 1);  // TODO: this is enough?
    WAIT(data_lo, 1, 2);
    WAIT(clock_hi, 50, 3);

    /* data [2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_lo, 50, 4);
        if (data_in()) {
            parity = !parity;
            data |= (1 << i);
        }
        WAIT(clock_hi, 50, 5);
    }

    /* parity [10] */
    WAIT(clock_lo, 50, 6);
    if (data_in() != parity) {
        ps2_error = PS2_ERR_PARITY;
        goto ERROR;
    }
    WAIT(clock_hi, 50, 7);

    /* stop bit [11] */
    WAIT(clock_lo, 50, 8);
    WAIT(data_hi, 1, 9);
    WAIT(clock_hi, 50, 10);

    inhibit();
    return data;
ERROR:
    if (ps2_error > PS2_ERR_STARTBIT3) {
        xprintf("x%02X\n", ps2_error);
    }
    inhibit();
    return 0;
}
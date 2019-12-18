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
 int /*<<< orphan*/  IBM4704_INT_OFF () ; 
 int /*<<< orphan*/  IBM4704_INT_ON () ; 
 int /*<<< orphan*/  WAIT (int /*<<< orphan*/  (*) (),int,int) ; 
 int /*<<< orphan*/  clock_hi () ; 
 int /*<<< orphan*/  clock_lo () ; 
 int /*<<< orphan*/  data_hi () ; 
 int /*<<< orphan*/  data_lo () ; 
 int ibm4704_error ; 
 int /*<<< orphan*/  idle () ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

uint8_t ibm4704_send(uint8_t data) {
    bool parity   = true;  // odd parity
    ibm4704_error = 0;

    IBM4704_INT_OFF();

    /* Request to send */
    idle();
    clock_lo();

    /* wait for Start bit(Clock:lo/Data:hi) */
    WAIT(data_hi, 300, 0x30);

    /* Data bit */
    for (uint8_t i = 0; i < 8; i++) {
        WAIT(clock_hi, 100, 0x40 + i);
        if (data & (1 << i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_lo, 100, 0x48 + i);
    }

    /* Parity bit */
    WAIT(clock_hi, 100, 0x34);
    if (parity) {
        data_hi();
    } else {
        data_lo();
    }
    WAIT(clock_lo, 100, 0x35);

    /* Stop bit */
    WAIT(clock_hi, 100, 0x34);
    data_hi();

    /* End */
    WAIT(data_lo, 100, 0x36);

    idle();
    IBM4704_INT_ON();
    return 0;
ERROR:
    idle();
    if (ibm4704_error > 0x30) {
        xprintf("S:%02X ", ibm4704_error);
    }
    IBM4704_INT_ON();
    return -1;
}
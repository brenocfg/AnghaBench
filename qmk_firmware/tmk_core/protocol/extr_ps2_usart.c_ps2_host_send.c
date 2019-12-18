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
 int /*<<< orphan*/  PS2_ERR_NONE ; 
 int /*<<< orphan*/  PS2_USART_INIT () ; 
 int /*<<< orphan*/  PS2_USART_OFF () ; 
 int /*<<< orphan*/  PS2_USART_RX_INT_ON () ; 
 int /*<<< orphan*/  WAIT (int /*<<< orphan*/  (*) (),int,int) ; 
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  clock_hi () ; 
 int /*<<< orphan*/  clock_lo () ; 
 int /*<<< orphan*/  data_hi () ; 
 int /*<<< orphan*/  data_lo () ; 
 int /*<<< orphan*/  idle () ; 
 int /*<<< orphan*/  inhibit () ; 
 int /*<<< orphan*/  ps2_error ; 
 int ps2_host_recv_response () ; 

uint8_t ps2_host_send(uint8_t data) {
    bool parity = true;
    ps2_error   = PS2_ERR_NONE;

    PS2_USART_OFF();

    /* terminate a transmission if we have */
    inhibit();
    _delay_us(100);  // [4]p.13

    /* 'Request to Send' and Start bit */
    data_lo();
    clock_hi();
    WAIT(clock_lo, 10000, 10);  // 10ms [5]p.50

    /* Data bit[2-9] */
    for (uint8_t i = 0; i < 8; i++) {
        _delay_us(15);
        if (data & (1 << i)) {
            parity = !parity;
            data_hi();
        } else {
            data_lo();
        }
        WAIT(clock_hi, 50, 2);
        WAIT(clock_lo, 50, 3);
    }

    /* Parity bit */
    _delay_us(15);
    if (parity) {
        data_hi();
    } else {
        data_lo();
    }
    WAIT(clock_hi, 50, 4);
    WAIT(clock_lo, 50, 5);

    /* Stop bit */
    _delay_us(15);
    data_hi();

    /* Ack */
    WAIT(data_lo, 50, 6);
    WAIT(clock_lo, 50, 7);

    /* wait for idle state */
    WAIT(clock_hi, 50, 8);
    WAIT(data_hi, 50, 9);

    idle();
    PS2_USART_INIT();
    PS2_USART_RX_INT_ON();
    return ps2_host_recv_response();
ERROR:
    idle();
    PS2_USART_INIT();
    PS2_USART_RX_INT_ON();
    return 0;
}
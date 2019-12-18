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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  _delay_us (int) ; 
 int /*<<< orphan*/  attention () ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  place_bit0 () ; 
 int /*<<< orphan*/  place_bit1 () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_byte (int /*<<< orphan*/ ) ; 

void adb_host_listen(uint8_t cmd, uint8_t data_h, uint8_t data_l) {
    cli();
    attention();
    send_byte(cmd);
    place_bit0();    // Stopbit(0)
    _delay_us(200);  // Tlt/Stop to Start
    place_bit1();    // Startbit(1)
    send_byte(data_h);
    send_byte(data_l);
    place_bit0();  // Stopbit(0);
    sei();
}
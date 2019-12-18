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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  attention () ; 
 int /*<<< orphan*/  cli () ; 
 int /*<<< orphan*/  place_bit0 () ; 
 int /*<<< orphan*/  sei () ; 
 int /*<<< orphan*/  send_byte (int) ; 
 int /*<<< orphan*/  wait_data_hi (int) ; 
 scalar_t__ wait_data_lo (int) ; 

__attribute__((used)) static inline uint16_t adb_host_dev_recv(uint8_t device) {
    uint16_t data = 0;
    cli();
    attention();
    send_byte(device | 0x0C);  // Addr:Keyboard(0010)/Mouse(0011), Cmd:Talk(11), Register0(00)
    place_bit0();              // Stopbit(0)
    if (!wait_data_hi(500)) {  // Service Request(310us Adjustable Keyboard): just ignored
        sei();
        return -30;  // something wrong
    }
    if (!wait_data_lo(500)) {  // Tlt/Stop to Start(140-260us)
        sei();
        return 0;  // No data to send
    }

    uint8_t n = 17;  // start bit + 16 data bits
    do {
        uint8_t lo = (uint8_t)wait_data_hi(130);
        if (!lo) goto error;

        uint8_t hi = (uint8_t)wait_data_lo(lo);
        if (!hi) goto error;

        hi = lo - hi;
        lo = 130 - lo;

        data <<= 1;
        if (lo < hi) {
            data |= 1;
        } else if (n == 17) {
            sei();
            return -20;
        }
    } while (--n);

    // Stop bit can't be checked normally since it could have service request lenghtening
    // and its high state never goes low.
    if (!wait_data_hi(351) || wait_data_lo(91)) {
        sei();
        return -21;
    }
    sei();
    return data;

error:
    sei();
    return -n;
}
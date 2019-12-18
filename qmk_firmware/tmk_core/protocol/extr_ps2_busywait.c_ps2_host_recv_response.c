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
 scalar_t__ ps2_error ; 
 int ps2_host_recv () ; 

uint8_t ps2_host_recv_response(void) {
    // Command may take 25ms/20ms at most([5]p.46, [3]p.21)
    // 250 * 100us(wait for start bit in ps2_host_recv)
    uint8_t data = 0;
    uint8_t try
        = 250;
    do {
        data = ps2_host_recv();
    } while (try --&&ps2_error);
    return data;
}
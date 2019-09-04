#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ rxRindex; scalar_t__ rxWindex; scalar_t__* rxBuffer; } ;

/* Variables and functions */
 TYPE_1__ telnet_data ; 

int telnet_rx_char (void) {
    int rx_char = -1;
    if (telnet_data.rxRindex != telnet_data.rxWindex) {
        // rxRindex must be uint8_t and TELNET_RX_BUFFER_SIZE == 256 so that it wraps around automatically
        rx_char = (int)telnet_data.rxBuffer[telnet_data.rxRindex++];
    }
    return rx_char;
}
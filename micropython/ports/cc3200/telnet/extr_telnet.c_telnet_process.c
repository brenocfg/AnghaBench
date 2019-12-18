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
typedef  int _i16 ;
struct TYPE_2__ {int rxWindex; int rxRindex; int /*<<< orphan*/ * rxBuffer; } ;

/* Variables and functions */
 scalar_t__ E_TELNET_RESULT_OK ; 
 int TELNET_RX_BUFFER_SIZE ; 
 TYPE_1__ telnet_data ; 
 scalar_t__ telnet_recv_text_non_blocking (int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static void telnet_process (void) {
    _i16 rxLen;
    _i16 maxLen = (telnet_data.rxWindex >= telnet_data.rxRindex) ? (TELNET_RX_BUFFER_SIZE - telnet_data.rxWindex) :
                                                                   ((telnet_data.rxRindex - telnet_data.rxWindex) - 1);
    // to avoid an overrrun
    maxLen = (telnet_data.rxRindex == 0) ? (maxLen - 1) : maxLen;

    if (maxLen > 0) {
        if (E_TELNET_RESULT_OK == telnet_recv_text_non_blocking(&telnet_data.rxBuffer[telnet_data.rxWindex], maxLen, &rxLen)) {
            // rxWindex must be uint8_t and TELNET_RX_BUFFER_SIZE == 256 so that it wraps around automatically
            telnet_data.rxWindex = telnet_data.rxWindex + rxLen;
        }
    }
}
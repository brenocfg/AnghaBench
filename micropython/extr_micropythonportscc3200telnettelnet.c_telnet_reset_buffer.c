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
struct TYPE_2__ {char* rxBuffer; int rxWindex; } ;

/* Variables and functions */
 int TELNET_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 TYPE_1__ telnet_data ; 

__attribute__((used)) static void telnet_reset_buffer (void) {
    // erase any characters present in the current line
    memset (telnet_data.rxBuffer, '\b', TELNET_RX_BUFFER_SIZE / 2);
    telnet_data.rxWindex = TELNET_RX_BUFFER_SIZE / 2;
    // fake an "enter" key pressed to display the prompt
    telnet_data.rxBuffer[telnet_data.rxWindex++] = '\r';
}
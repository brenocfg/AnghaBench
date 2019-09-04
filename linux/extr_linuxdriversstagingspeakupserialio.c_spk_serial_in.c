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
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 int SPK_SERIAL_TIMEOUT ; 
 scalar_t__ UART_LSR ; 
 unsigned char UART_LSR_DR ; 
 scalar_t__ UART_RX ; 
 unsigned char inb_p (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned char spk_serial_in(void)
{
	int tmout = SPK_SERIAL_TIMEOUT;

	while (!(inb_p(speakup_info.port_tts + UART_LSR) & UART_LSR_DR)) {
		if (--tmout == 0) {
			pr_warn("time out while waiting for input.\n");
			return 0xff;
		}
		udelay(1);
	}
	return inb_p(speakup_info.port_tts + UART_RX);
}
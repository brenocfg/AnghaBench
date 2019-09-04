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
struct TYPE_2__ {int /*<<< orphan*/  port_tts; } ;

/* Variables and functions */
 int SPK_XMITR_TIMEOUT ; 
 int /*<<< orphan*/  outb (char,int /*<<< orphan*/ ) ; 
 TYPE_1__ speakup_info ; 
 scalar_t__ spk_serial_tx_busy () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void spk_serial_send_xchar(char ch)
{
	int timeout = SPK_XMITR_TIMEOUT;

	while (spk_serial_tx_busy()) {
		if (!--timeout)
			break;
		udelay(1);
	}
	outb(ch, speakup_info.port_tts);
}
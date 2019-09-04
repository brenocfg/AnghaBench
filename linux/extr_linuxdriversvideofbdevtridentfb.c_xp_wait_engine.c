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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int t_inb (struct tridentfb_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xp_wait_engine(struct tridentfb_par *par)
{
	int count = 0;
	int timeout = 0;

	while (t_inb(par, STATUS) & 0x80) {
		count++;
		if (count == 10000000) {
			/* Timeout */
			count = 9990000;
			timeout++;
			if (timeout == 8) {
				/* Reset engine */
				t_outb(par, 0x00, STATUS);
				return;
			}
		}
		cpu_relax();
	}
}
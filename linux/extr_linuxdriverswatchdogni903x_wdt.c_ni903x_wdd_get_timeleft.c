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
typedef  int u8 ;
typedef  int u32 ;
struct watchdog_device {int dummy; } ;
struct ni903x_wdt {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ NIWD_CONTROL ; 
 int NIWD_CONTROL_CAPTURECOUNTER ; 
 scalar_t__ NIWD_COUNTER0 ; 
 scalar_t__ NIWD_COUNTER1 ; 
 scalar_t__ NIWD_COUNTER2 ; 
 int NIWD_PERIOD_NS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 struct ni903x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int ni903x_wdd_get_timeleft(struct watchdog_device *wdd)
{
	struct ni903x_wdt *wdt = watchdog_get_drvdata(wdd);
	u8 control, counter0, counter1, counter2;
	u32 counter;

	control = inb(wdt->io_base + NIWD_CONTROL);
	control |= NIWD_CONTROL_CAPTURECOUNTER;
	outb(control, wdt->io_base + NIWD_CONTROL);

	counter2 = inb(wdt->io_base + NIWD_COUNTER2);
	counter1 = inb(wdt->io_base + NIWD_COUNTER1);
	counter0 = inb(wdt->io_base + NIWD_COUNTER0);

	counter = (counter2 << 16) | (counter1 << 8) | counter0;

	return counter / (1000000000 / NIWD_PERIOD_NS);
}
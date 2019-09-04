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
struct TYPE_2__ {int /*<<< orphan*/  io_lock; scalar_t__ runtime_reg; } ;

/* Variables and functions */
 scalar_t__ GP60 ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 TYPE_1__ sch311x_wdt_data ; 
 int /*<<< orphan*/  sch311x_wdt_set_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sch311x_wdt_stop(void)
{
	unsigned char t;

	spin_lock(&sch311x_wdt_data.io_lock);

	/* stop the watchdog */
	t = inb(sch311x_wdt_data.runtime_reg + GP60);
	outb((t & ~0x0d) | 0x01, sch311x_wdt_data.runtime_reg + GP60);
	/* disable timeout by setting it to 0 */
	sch311x_wdt_set_timeout(0);

	spin_unlock(&sch311x_wdt_data.io_lock);
}
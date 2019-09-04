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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sioaddr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F71808FG_FLAG_WD_EN ; 
 int /*<<< orphan*/  F71808FG_REG_WDT_CONF ; 
 int /*<<< orphan*/  SIO_F71808FG_LD_WDT ; 
 int /*<<< orphan*/  SIO_REG_ENABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ superio_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_exit (int /*<<< orphan*/ ) ; 
 int superio_inb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ watchdog ; 

__attribute__((used)) static bool watchdog_is_running(void)
{
	/*
	 * if we fail to determine the watchdog's status assume it to be
	 * running to be on the safe side
	 */
	bool is_running = true;

	mutex_lock(&watchdog.lock);
	if (superio_enter(watchdog.sioaddr))
		goto exit_unlock;
	superio_select(watchdog.sioaddr, SIO_F71808FG_LD_WDT);

	is_running = (superio_inb(watchdog.sioaddr, SIO_REG_ENABLE) & BIT(0))
		&& (superio_inb(watchdog.sioaddr, F71808FG_REG_WDT_CONF)
			& BIT(F71808FG_FLAG_WD_EN));

	superio_exit(watchdog.sioaddr);

exit_unlock:
	mutex_unlock(&watchdog.lock);
	return is_running;
}
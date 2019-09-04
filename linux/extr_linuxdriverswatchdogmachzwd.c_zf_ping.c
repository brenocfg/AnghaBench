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
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_2 ; 
 unsigned int RESET_WD1 ; 
 scalar_t__ ZF_HW_TIMEO ; 
 int /*<<< orphan*/  dprintk (char*,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ next_heartbeat ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 
 unsigned int zf_get_control () ; 
 int /*<<< orphan*/  zf_port_lock ; 
 int /*<<< orphan*/  zf_set_control (unsigned int) ; 
 int /*<<< orphan*/  zf_timer ; 
 int /*<<< orphan*/  zf_writeb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zf_ping(struct timer_list *unused)
{
	unsigned int ctrl_reg = 0;
	unsigned long flags;

	zf_writeb(COUNTER_2, 0xff);

	if (time_before(jiffies, next_heartbeat)) {
		dprintk("time_before: %ld\n", next_heartbeat - jiffies);
		/*
		 * reset event is activated by transition from 0 to 1 on
		 * RESET_WD1 bit and we assume that it is already zero...
		 */

		spin_lock_irqsave(&zf_port_lock, flags);
		ctrl_reg = zf_get_control();
		ctrl_reg |= RESET_WD1;
		zf_set_control(ctrl_reg);

		/* ...and nothing changes until here */
		ctrl_reg &= ~(RESET_WD1);
		zf_set_control(ctrl_reg);
		spin_unlock_irqrestore(&zf_port_lock, flags);

		mod_timer(&zf_timer, jiffies + ZF_HW_TIMEO);
	} else
		pr_crit("I will reset your machine\n");
}
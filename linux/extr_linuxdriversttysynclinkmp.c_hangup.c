#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; TYPE_1__* driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  open_wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; scalar_t__ count; } ;
struct TYPE_5__ {TYPE_2__ port; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sanity_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_set_active (TYPE_2__*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hangup(struct tty_struct *tty)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s hangup()\n",
			 __FILE__,__LINE__, info->device_name );

	if (sanity_check(info, tty->name, "hangup"))
		return;

	mutex_lock(&info->port.mutex);
	flush_buffer(tty);
	shutdown(info);

	spin_lock_irqsave(&info->port.lock, flags);
	info->port.count = 0;
	info->port.tty = NULL;
	spin_unlock_irqrestore(&info->port.lock, flags);
	tty_port_set_active(&info->port, 1);
	mutex_unlock(&info->port.mutex);

	wake_up_interruptible(&info->port.open_wait);
}
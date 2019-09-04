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
struct tty_struct {int /*<<< orphan*/  name; struct slgt_info* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tty; scalar_t__ count; } ;
struct slgt_info {TYPE_1__ port; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGINFO (char*) ; 
 int /*<<< orphan*/  flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sanity_check (struct slgt_info*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (struct slgt_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_port_set_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hangup(struct tty_struct *tty)
{
	struct slgt_info *info = tty->driver_data;
	unsigned long flags;

	if (sanity_check(info, tty->name, "hangup"))
		return;
	DBGINFO(("%s hangup\n", info->device_name));

	flush_buffer(tty);

	mutex_lock(&info->port.mutex);
	shutdown(info);

	spin_lock_irqsave(&info->port.lock, flags);
	info->port.count = 0;
	info->port.tty = NULL;
	spin_unlock_irqrestore(&info->port.lock, flags);
	tty_port_set_active(&info->port, 0);
	mutex_unlock(&info->port.mutex);

	wake_up_interruptible(&info->port.open_wait);
}
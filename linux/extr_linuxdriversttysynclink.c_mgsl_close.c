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
struct tty_struct {TYPE_1__* driver; int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  count; int /*<<< orphan*/ * tty; int /*<<< orphan*/  mutex; } ;
struct mgsl_struct {TYPE_2__ port; int /*<<< orphan*/  timeout; int /*<<< orphan*/  device_name; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_flush_buffer (struct tty_struct*) ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mgsl_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (struct mgsl_struct*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (TYPE_2__*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (TYPE_2__*,struct tty_struct*,struct file*) ; 
 scalar_t__ tty_port_initialized (TYPE_2__*) ; 

__attribute__((used)) static void mgsl_close(struct tty_struct *tty, struct file * filp)
{
	struct mgsl_struct * info = tty->driver_data;

	if (mgsl_paranoia_check(info, tty->name, "mgsl_close"))
		return;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_close(%s) entry, count=%d\n",
			 __FILE__,__LINE__, info->device_name, info->port.count);

	if (tty_port_close_start(&info->port, tty, filp) == 0)
		goto cleanup;

	mutex_lock(&info->port.mutex);
	if (tty_port_initialized(&info->port))
 		mgsl_wait_until_sent(tty, info->timeout);
	mgsl_flush_buffer(tty);
	tty_ldisc_flush(tty);
	shutdown(info);
	mutex_unlock(&info->port.mutex);

	tty_port_close_end(&info->port, tty);	
	info->port.tty = NULL;
cleanup:			
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_close(%s) exit, count=%d\n", __FILE__,__LINE__,
			tty->driver->name, info->port.count);
			
}
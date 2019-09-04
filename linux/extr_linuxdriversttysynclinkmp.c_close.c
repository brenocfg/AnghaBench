#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* driver; int /*<<< orphan*/  name; TYPE_2__* driver_data; } ;
struct file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  count; int /*<<< orphan*/ * tty; int /*<<< orphan*/  mutex; } ;
struct TYPE_9__ {TYPE_3__ port; int /*<<< orphan*/  timeout; int /*<<< orphan*/  device_name; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sanity_check (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_close_end (TYPE_3__*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (TYPE_3__*,struct tty_struct*,struct file*) ; 
 scalar_t__ tty_port_initialized (TYPE_3__*) ; 
 int /*<<< orphan*/  wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void close(struct tty_struct *tty, struct file *filp)
{
	SLMP_INFO * info = tty->driver_data;

	if (sanity_check(info, tty->name, "close"))
		return;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s close() entry, count=%d\n",
			 __FILE__,__LINE__, info->device_name, info->port.count);

	if (tty_port_close_start(&info->port, tty, filp) == 0)
		goto cleanup;

	mutex_lock(&info->port.mutex);
	if (tty_port_initialized(&info->port))
 		wait_until_sent(tty, info->timeout);

	flush_buffer(tty);
	tty_ldisc_flush(tty);
	shutdown(info);
	mutex_unlock(&info->port.mutex);

	tty_port_close_end(&info->port, tty);
	info->port.tty = NULL;
cleanup:
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s close() exit, count=%d\n", __FILE__,__LINE__,
			tty->driver->name, info->port.count);
}
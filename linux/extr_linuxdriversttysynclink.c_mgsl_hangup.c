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
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  open_wait; int /*<<< orphan*/ * tty; scalar_t__ count; } ;
struct mgsl_struct {TYPE_1__ port; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  mgsl_flush_buffer (struct tty_struct*) ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown (struct mgsl_struct*) ; 
 int /*<<< orphan*/  tty_port_set_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgsl_hangup(struct tty_struct *tty)
{
	struct mgsl_struct * info = tty->driver_data;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_hangup(%s)\n",
			 __FILE__,__LINE__, info->device_name );
			 
	if (mgsl_paranoia_check(info, tty->name, "mgsl_hangup"))
		return;

	mgsl_flush_buffer(tty);
	shutdown(info);
	
	info->port.count = 0;	
	tty_port_set_active(&info->port, 0);
	info->port.tty = NULL;

	wake_up_interruptible(&info->port.open_wait);
	
}
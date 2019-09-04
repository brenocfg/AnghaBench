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
struct tty_struct {int /*<<< orphan*/  name; struct mgsl_struct* driver_data; } ;
struct mgsl_struct {int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EIO ; 
 int ENODEV ; 
 unsigned int TIOCGSERIAL ; 
 unsigned int TIOCMIWAIT ; 
 unsigned int TIOCSSERIAL ; 
 scalar_t__ debug_level ; 
 int mgsl_ioctl_common (struct mgsl_struct*,unsigned int,unsigned long) ; 
 scalar_t__ mgsl_paranoia_check (struct mgsl_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ tty_io_error (struct tty_struct*) ; 

__attribute__((used)) static int mgsl_ioctl(struct tty_struct *tty,
		    unsigned int cmd, unsigned long arg)
{
	struct mgsl_struct * info = tty->driver_data;
	
	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgsl_ioctl %s cmd=%08X\n", __FILE__,__LINE__,
			info->device_name, cmd );
	
	if (mgsl_paranoia_check(info, tty->name, "mgsl_ioctl"))
		return -ENODEV;

	if ((cmd != TIOCGSERIAL) && (cmd != TIOCSSERIAL) &&
	    (cmd != TIOCMIWAIT)) {
		if (tty_io_error(tty))
		    return -EIO;
	}

	return mgsl_ioctl_common(info, cmd, arg);
}
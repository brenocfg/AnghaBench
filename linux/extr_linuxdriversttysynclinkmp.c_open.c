#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int count; TYPE_1__* driver; TYPE_3__* driver_data; } ;
struct file {int dummy; } ;
struct TYPE_7__ {int count; int low_latency; long flags; struct tty_struct* tty; } ;
struct TYPE_8__ {TYPE_2__ port; int /*<<< orphan*/  device_name; int /*<<< orphan*/  netlock; scalar_t__ netcount; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ SLMP_INFO ;

/* Variables and functions */
 long ASYNC_LOW_LATENCY ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EBUSY ; 
 int block_til_ready (struct tty_struct*,struct file*,TYPE_3__*) ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int startup (TYPE_3__*) ; 

__attribute__((used)) static int open(struct tty_struct *tty, struct file *filp)
{
	SLMP_INFO *info = tty->driver_data;
	unsigned long flags;
	int retval;

	info->port.tty = tty;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s open(), old ref count = %d\n",
			 __FILE__,__LINE__,tty->driver->name, info->port.count);

	info->port.low_latency = (info->port.flags & ASYNC_LOW_LATENCY) ? 1 : 0;

	spin_lock_irqsave(&info->netlock, flags);
	if (info->netcount) {
		retval = -EBUSY;
		spin_unlock_irqrestore(&info->netlock, flags);
		goto cleanup;
	}
	info->port.count++;
	spin_unlock_irqrestore(&info->netlock, flags);

	if (info->port.count == 1) {
		/* 1st open on this device, init hardware */
		retval = startup(info);
		if (retval < 0)
			goto cleanup;
	}

	retval = block_til_ready(tty, filp, info);
	if (retval) {
		if (debug_level >= DEBUG_LEVEL_INFO)
			printk("%s(%d):%s block_til_ready() returned %d\n",
				 __FILE__,__LINE__, info->device_name, retval);
		goto cleanup;
	}

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s open() success\n",
			 __FILE__,__LINE__, info->device_name);
	retval = 0;

cleanup:
	if (retval) {
		if (tty->count == 1)
			info->port.tty = NULL; /* tty layer will release tty struct */
		if(info->port.count)
			info->port.count--;
	}

	return retval;
}
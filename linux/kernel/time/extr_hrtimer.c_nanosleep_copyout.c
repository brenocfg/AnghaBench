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
struct timespec64 {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  rmtp; int /*<<< orphan*/  compat_rmtp; } ;
struct restart_block {TYPE_1__ nanosleep; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EFAULT ; 
 int ERESTART_RESTARTBLOCK ; 
#define  TT_COMPAT 129 
#define  TT_NATIVE 128 
 int /*<<< orphan*/  put_old_timespec32 (struct timespec64*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_timespec64 (struct timespec64*,int /*<<< orphan*/ ) ; 

int nanosleep_copyout(struct restart_block *restart, struct timespec64 *ts)
{
	switch(restart->nanosleep.type) {
#ifdef CONFIG_COMPAT_32BIT_TIME
	case TT_COMPAT:
		if (put_old_timespec32(ts, restart->nanosleep.compat_rmtp))
			return -EFAULT;
		break;
#endif
	case TT_NATIVE:
		if (put_timespec64(ts, restart->nanosleep.rmtp))
			return -EFAULT;
		break;
	default:
		BUG();
	}
	return -ERESTART_RESTARTBLOCK;
}
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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  SHUTDOWN_POWEROFF ; 
#define  SYS_DOWN 130 
#define  SYS_HALT 129 
#define  SYS_POWER_OFF 128 
 int /*<<< orphan*/  shutting_down ; 

__attribute__((used)) static int poweroff_nb(struct notifier_block *cb, unsigned long code, void *unused)
{
	switch (code) {
	case SYS_DOWN:
	case SYS_HALT:
	case SYS_POWER_OFF:
		shutting_down = SHUTDOWN_POWEROFF;
	default:
		break;
	}
	return NOTIFY_DONE;
}
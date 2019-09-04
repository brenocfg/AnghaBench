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
struct TYPE_2__ {long expires; } ;
struct delayed_work {TYPE_1__ timer; } ;

/* Variables and functions */
 int cancel_delayed_work (struct delayed_work*) ; 
 long jiffies ; 

__attribute__((used)) static long cw1200_suspend_work(struct delayed_work *work)
{
	int ret = cancel_delayed_work(work);
	long tmo;
	if (ret > 0) {
		/* Timer is pending */
		tmo = work->timer.expires - jiffies;
		if (tmo < 0)
			tmo = 0;
	} else {
		tmo = -1;
	}
	return tmo;
}
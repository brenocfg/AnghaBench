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
struct ceph_mon_client {unsigned long hunt_mult; int /*<<< orphan*/  delayed_work; scalar_t__ hunting; } ;

/* Variables and functions */
 unsigned long CEPH_MONC_HUNT_INTERVAL ; 
 unsigned long CEPH_MONC_PING_INTERVAL ; 
 int /*<<< orphan*/  dout (char*,unsigned long) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_jiffies_relative (unsigned long) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void __schedule_delayed(struct ceph_mon_client *monc)
{
	unsigned long delay;

	if (monc->hunting)
		delay = CEPH_MONC_HUNT_INTERVAL * monc->hunt_mult;
	else
		delay = CEPH_MONC_PING_INTERVAL;

	dout("__schedule_delayed after %lu\n", delay);
	mod_delayed_work(system_wq, &monc->delayed_work,
			 round_jiffies_relative(delay));
}
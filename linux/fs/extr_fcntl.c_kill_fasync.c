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
struct fasync_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kill_fasync_rcu (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rcu_dereference (struct fasync_struct*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void kill_fasync(struct fasync_struct **fp, int sig, int band)
{
	/* First a quick test without locking: usually
	 * the list is empty.
	 */
	if (*fp) {
		rcu_read_lock();
		kill_fasync_rcu(rcu_dereference(*fp), sig, band);
		rcu_read_unlock();
	}
}
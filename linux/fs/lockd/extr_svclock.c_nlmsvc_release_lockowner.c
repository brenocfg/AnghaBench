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
struct TYPE_2__ {scalar_t__ fl_owner; } ;
struct nlm_lock {TYPE_1__ fl; } ;

/* Variables and functions */
 int /*<<< orphan*/  nlmsvc_put_lockowner (scalar_t__) ; 

void
nlmsvc_release_lockowner(struct nlm_lock *lock)
{
	if (lock->fl.fl_owner)
		nlmsvc_put_lockowner(lock->fl.fl_owner);
}
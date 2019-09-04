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
struct inet6_ifaddr {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ INET6_IFADDR_STATE_DAD ; 
 scalar_t__ INET6_IFADDR_STATE_POSTDAD ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int addrconf_dad_end(struct inet6_ifaddr *ifp)
{
	int err = -ENOENT;

	spin_lock_bh(&ifp->lock);
	if (ifp->state == INET6_IFADDR_STATE_DAD) {
		ifp->state = INET6_IFADDR_STATE_POSTDAD;
		err = 0;
	}
	spin_unlock_bh(&ifp->lock);

	return err;
}
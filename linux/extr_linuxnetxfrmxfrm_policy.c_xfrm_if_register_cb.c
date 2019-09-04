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
struct xfrm_if_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct xfrm_if_cb const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_if_cb ; 
 int /*<<< orphan*/  xfrm_if_cb_lock ; 

void xfrm_if_register_cb(const struct xfrm_if_cb *ifcb)
{
	spin_lock(&xfrm_if_cb_lock);
	rcu_assign_pointer(xfrm_if_cb, ifcb);
	spin_unlock(&xfrm_if_cb_lock);
}
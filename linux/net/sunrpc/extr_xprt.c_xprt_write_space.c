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
struct rpc_xprt {int /*<<< orphan*/  transport_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  XPRT_WRITE_SPACE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xprt_clear_write_space_locked (struct rpc_xprt*) ; 

bool xprt_write_space(struct rpc_xprt *xprt)
{
	bool ret;

	if (!test_bit(XPRT_WRITE_SPACE, &xprt->state))
		return false;
	spin_lock(&xprt->transport_lock);
	ret = xprt_clear_write_space_locked(xprt);
	spin_unlock(&xprt->transport_lock);
	return ret;
}
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
struct xdp_sock {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ XSK_BOUND ; 
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static bool xsk_is_bound(struct xdp_sock *xs)
{
	if (READ_ONCE(xs->state) == XSK_BOUND) {
		/* Matches smp_wmb() in bind(). */
		smp_rmb();
		return true;
	}
	return false;
}
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
struct tb_xdomain {int /*<<< orphan*/  lock; int /*<<< orphan*/  tb; scalar_t__ receive_ring; scalar_t__ receive_path; scalar_t__ transmit_ring; scalar_t__ transmit_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tb_domain_disconnect_xdomain_paths (int /*<<< orphan*/ ,struct tb_xdomain*) ; 

int tb_xdomain_disable_paths(struct tb_xdomain *xd)
{
	int ret = 0;

	mutex_lock(&xd->lock);
	if (xd->transmit_path) {
		xd->transmit_path = 0;
		xd->transmit_ring = 0;
		xd->receive_path = 0;
		xd->receive_ring = 0;

		ret = tb_domain_disconnect_xdomain_paths(xd->tb, xd);
	}
	mutex_unlock(&xd->lock);

	return ret;
}
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
struct vsock_tap {int /*<<< orphan*/  list; int /*<<< orphan*/  module; TYPE_1__* dev; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_VSOCKMON ; 
 int EINVAL ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vsock_tap_all ; 
 int /*<<< orphan*/  vsock_tap_lock ; 

int vsock_add_tap(struct vsock_tap *vt)
{
	if (unlikely(vt->dev->type != ARPHRD_VSOCKMON))
		return -EINVAL;

	__module_get(vt->module);

	spin_lock(&vsock_tap_lock);
	list_add_rcu(&vt->list, &vsock_tap_all);
	spin_unlock(&vsock_tap_lock);

	return 0;
}
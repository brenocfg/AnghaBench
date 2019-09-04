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
struct mtu3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  g; TYPE_1__* gadget_driver; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* resume ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void mtu3_gadget_resume(struct mtu3 *mtu)
{
	dev_dbg(mtu->dev, "gadget RESUME\n");
	if (mtu->gadget_driver && mtu->gadget_driver->resume) {
		spin_unlock(&mtu->lock);
		mtu->gadget_driver->resume(&mtu->g);
		spin_lock(&mtu->lock);
	}
}
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
struct atalk_addr {int dummy; } ;
struct atalk_iface {struct atalk_addr address; TYPE_1__* dev; struct atalk_iface* next; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_POINTOPOINT ; 
 struct atalk_iface* atalk_interfaces ; 
 int /*<<< orphan*/  atalk_interfaces_lock ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct atalk_addr *atalk_find_primary(void)
{
	struct atalk_iface *fiface = NULL;
	struct atalk_addr *retval;
	struct atalk_iface *iface;

	/*
	 * Return a point-to-point interface only if
	 * there is no non-ptp interface available.
	 */
	read_lock_bh(&atalk_interfaces_lock);
	for (iface = atalk_interfaces; iface; iface = iface->next) {
		if (!fiface && !(iface->dev->flags & IFF_LOOPBACK))
			fiface = iface;
		if (!(iface->dev->flags & (IFF_LOOPBACK | IFF_POINTOPOINT))) {
			retval = &iface->address;
			goto out;
		}
	}

	if (fiface)
		retval = &fiface->address;
	else if (atalk_interfaces)
		retval = &atalk_interfaces->address;
	else
		retval = NULL;
out:
	read_unlock_bh(&atalk_interfaces_lock);
	return retval;
}
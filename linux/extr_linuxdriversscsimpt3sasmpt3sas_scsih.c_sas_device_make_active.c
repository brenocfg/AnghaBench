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
struct _sas_device {int /*<<< orphan*/  list; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; int /*<<< orphan*/  sas_device_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_device_get (struct _sas_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sas_device_make_active(struct MPT3SAS_ADAPTER *ioc,
		struct _sas_device *sas_device)
{
	unsigned long flags;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);

	/*
	 * Since we dropped the lock during the call to port_add(), we need to
	 * be careful here that somebody else didn't move or delete this item
	 * while we were busy with other things.
	 *
	 * If it was on the list, we need a put() for the reference the list
	 * had. Either way, we need a get() for the destination list.
	 */
	if (!list_empty(&sas_device->list)) {
		list_del_init(&sas_device->list);
		sas_device_put(sas_device);
	}

	sas_device_get(sas_device);
	list_add_tail(&sas_device->list, &ioc->sas_device_list);

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
}
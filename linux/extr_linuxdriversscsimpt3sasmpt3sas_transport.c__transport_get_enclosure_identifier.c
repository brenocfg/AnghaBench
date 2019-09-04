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
typedef  scalar_t__ u64 ;
struct TYPE_2__ {int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {TYPE_1__ identify; } ;
struct _sas_device {scalar_t__ enclosure_logical_id; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  sas_device_lock; } ;

/* Variables and functions */
 int ENXIO ; 
 struct _sas_device* __mpt3sas_get_sdev_by_addr (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 struct MPT3SAS_ADAPTER* rphy_to_ioc (struct sas_rphy*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
_transport_get_enclosure_identifier(struct sas_rphy *rphy, u64 *identifier)
{
	struct MPT3SAS_ADAPTER *ioc = rphy_to_ioc(rphy);
	struct _sas_device *sas_device;
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&ioc->sas_device_lock, flags);
	sas_device = __mpt3sas_get_sdev_by_addr(ioc,
	    rphy->identify.sas_address);
	if (sas_device) {
		*identifier = sas_device->enclosure_logical_id;
		rc = 0;
		sas_device_put(sas_device);
	} else {
		*identifier = 0;
		rc = -ENXIO;
	}

	spin_unlock_irqrestore(&ioc->sas_device_lock, flags);
	return rc;
}
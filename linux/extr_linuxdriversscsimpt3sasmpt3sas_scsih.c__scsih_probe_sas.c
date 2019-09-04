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
struct _sas_device {int /*<<< orphan*/  sas_address_parent; int /*<<< orphan*/  sas_address; int /*<<< orphan*/  starget; int /*<<< orphan*/  handle; } ;
struct MPT3SAS_ADAPTER {int /*<<< orphan*/  is_driver_loading; scalar_t__ hide_drives; } ;

/* Variables and functions */
 int /*<<< orphan*/  _scsih_sas_device_remove (struct MPT3SAS_ADAPTER*,struct _sas_device*) ; 
 struct _sas_device* get_next_sas_device (struct MPT3SAS_ADAPTER*) ; 
 int /*<<< orphan*/  mpt3sas_transport_port_add (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt3sas_transport_port_remove (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_device_make_active (struct MPT3SAS_ADAPTER*,struct _sas_device*) ; 
 int /*<<< orphan*/  sas_device_put (struct _sas_device*) ; 

__attribute__((used)) static void
_scsih_probe_sas(struct MPT3SAS_ADAPTER *ioc)
{
	struct _sas_device *sas_device;

	if (ioc->hide_drives)
		return;

	while ((sas_device = get_next_sas_device(ioc))) {
		if (!mpt3sas_transport_port_add(ioc, sas_device->handle,
		    sas_device->sas_address_parent)) {
			_scsih_sas_device_remove(ioc, sas_device);
			sas_device_put(sas_device);
			continue;
		} else if (!sas_device->starget) {
			/*
			 * When asyn scanning is enabled, its not possible to
			 * remove devices while scanning is turned on due to an
			 * oops in scsi_sysfs_add_sdev()->add_device()->
			 * sysfs_addrm_start()
			 */
			if (!ioc->is_driver_loading) {
				mpt3sas_transport_port_remove(ioc,
				    sas_device->sas_address,
				    sas_device->sas_address_parent);
				_scsih_sas_device_remove(ioc, sas_device);
				sas_device_put(sas_device);
				continue;
			}
		}
		sas_device_make_active(ioc, sas_device);
		sas_device_put(sas_device);
	}
}
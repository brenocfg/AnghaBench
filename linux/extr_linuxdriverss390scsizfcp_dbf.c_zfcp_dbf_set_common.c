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
struct zfcp_port {int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwpn; int /*<<< orphan*/  status; } ;
struct zfcp_dbf_rec {int /*<<< orphan*/  lun; void* lun_status; int /*<<< orphan*/  d_id; int /*<<< orphan*/  wwpn; void* port_status; void* adapter_status; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; } ;
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZFCP_DBF_INVALID_LUN ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_scsi_dev_lun (struct scsi_device*) ; 

__attribute__((used)) static void zfcp_dbf_set_common(struct zfcp_dbf_rec *rec,
				struct zfcp_adapter *adapter,
				struct zfcp_port *port,
				struct scsi_device *sdev)
{
	rec->adapter_status = atomic_read(&adapter->status);
	if (port) {
		rec->port_status = atomic_read(&port->status);
		rec->wwpn = port->wwpn;
		rec->d_id = port->d_id;
	}
	if (sdev) {
		rec->lun_status = atomic_read(&sdev_to_zfcp(sdev)->status);
		rec->lun = zfcp_scsi_dev_lun(sdev);
	} else
		rec->lun = ZFCP_DBF_INVALID_LUN;
}
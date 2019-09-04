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
typedef  int /*<<< orphan*/  u64 ;
struct zfcp_unit {struct zfcp_port* port; int /*<<< orphan*/  fcp_lun; } ;
struct zfcp_port {int /*<<< orphan*/  starget_id; TYPE_1__* adapter; } ;
struct scsi_lun {int dummy; } ;
struct scsi_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {struct Scsi_Host* scsi_host; } ;

/* Variables and functions */
 struct scsi_device* scsi_device_lookup (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsilun_to_int (struct scsi_lun*) ; 

struct scsi_device *zfcp_unit_sdev(struct zfcp_unit *unit)
{
	struct Scsi_Host *shost;
	struct zfcp_port *port;
	u64 lun;

	lun = scsilun_to_int((struct scsi_lun *) &unit->fcp_lun);
	port = unit->port;
	shost = port->adapter->scsi_host;
	return scsi_device_lookup(shost, 0, port->starget_id, lun);
}
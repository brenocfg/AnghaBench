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
struct zfcp_port {int /*<<< orphan*/  dev; } ;
struct zfcp_adapter {int dummy; } ;
struct fc_rport {int /*<<< orphan*/  port_id; int /*<<< orphan*/  port_name; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 struct Scsi_Host* rport_to_shost (struct fc_rport*) ; 
 int /*<<< orphan*/  zfcp_erp_port_forced_no_port_dbf (char*,struct zfcp_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_erp_port_forced_reopen (struct zfcp_port*,int /*<<< orphan*/ ,char*) ; 
 struct zfcp_port* zfcp_get_port_by_wwpn (struct zfcp_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zfcp_scsi_terminate_rport_io(struct fc_rport *rport)
{
	struct zfcp_port *port;
	struct Scsi_Host *shost = rport_to_shost(rport);
	struct zfcp_adapter *adapter =
		(struct zfcp_adapter *)shost->hostdata[0];

	port = zfcp_get_port_by_wwpn(adapter, rport->port_name);

	if (port) {
		zfcp_erp_port_forced_reopen(port, 0, "sctrpi1");
		put_device(&port->dev);
	} else {
		zfcp_erp_port_forced_no_port_dbf(
			"sctrpin", adapter,
			rport->port_name /* zfcp_scsi_rport_register */,
			rport->port_id /* zfcp_scsi_rport_register */);
	}
}
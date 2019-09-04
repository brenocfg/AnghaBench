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
struct iscsi_cls_host {int /*<<< orphan*/  port_speed; } ;
struct beiscsi_hba {int port_speed; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;

/* Variables and functions */
#define  BE2ISCSI_LINK_SPEED_100MBPS 133 
#define  BE2ISCSI_LINK_SPEED_10GBPS 132 
#define  BE2ISCSI_LINK_SPEED_10MBPS 131 
#define  BE2ISCSI_LINK_SPEED_1GBPS 130 
#define  BE2ISCSI_LINK_SPEED_25GBPS 129 
#define  BE2ISCSI_LINK_SPEED_40GBPS 128 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_100MBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_10GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_10MBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_1GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_25GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_40GBPS ; 
 int /*<<< orphan*/  ISCSI_PORT_SPEED_UNKNOWN ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 

__attribute__((used)) static void beiscsi_get_port_speed(struct Scsi_Host *shost)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct iscsi_cls_host *ihost = shost->shost_data;

	switch (phba->port_speed) {
	case BE2ISCSI_LINK_SPEED_10MBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10MBPS;
		break;
	case BE2ISCSI_LINK_SPEED_100MBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_100MBPS;
		break;
	case BE2ISCSI_LINK_SPEED_1GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_1GBPS;
		break;
	case BE2ISCSI_LINK_SPEED_10GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_10GBPS;
		break;
	case BE2ISCSI_LINK_SPEED_25GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_25GBPS;
		break;
	case BE2ISCSI_LINK_SPEED_40GBPS:
		ihost->port_speed = ISCSI_PORT_SPEED_40GBPS;
		break;
	default:
		ihost->port_speed = ISCSI_PORT_SPEED_UNKNOWN;
	}
}
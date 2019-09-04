#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct iscsi_cls_host {int port_speed; } ;
struct Scsi_Host {struct iscsi_cls_host* shost_data; } ;
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* iscsi_port_speed_names ; 

char *iscsi_get_port_speed_name(struct Scsi_Host *shost)
{
	int i;
	char *speed = "Unknown!";
	struct iscsi_cls_host *ihost = shost->shost_data;
	uint32_t port_speed = ihost->port_speed;

	for (i = 0; i < ARRAY_SIZE(iscsi_port_speed_names); i++) {
		if (iscsi_port_speed_names[i].value & port_speed) {
			speed = iscsi_port_speed_names[i].name;
			break;
		}
	}
	return speed;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct nvram {TYPE_3__* bus; } ;
struct scsi_qla_host {TYPE_2__* bus_settings; struct nvram nvram; } ;
struct TYPE_4__ {int initiator_id; int /*<<< orphan*/  scsi_reset_disable; } ;
struct TYPE_6__ {scalar_t__ max_queue_depth; int /*<<< orphan*/  bus_reset_delay; TYPE_1__ config_1; } ;
struct TYPE_5__ {int id; scalar_t__ hiwat; int /*<<< orphan*/  bus_reset_delay; int /*<<< orphan*/  disable_scsi_reset; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_1 ; 
 int BIT_7 ; 
 int MAILBOX_REGISTER_COUNT ; 
 int MAX_TARGETS ; 
 int MBC_SET_INITIATOR_ID ; 
 int qla1280_config_target (struct scsi_qla_host*,int,int) ; 
 int qla1280_mailbox_command (struct scsi_qla_host*,int,int*) ; 

__attribute__((used)) static int
qla1280_config_bus(struct scsi_qla_host *ha, int bus)
{
	struct nvram *nv = &ha->nvram;
	uint16_t mb[MAILBOX_REGISTER_COUNT];
	int target, status;

	/* SCSI Reset Disable. */
	ha->bus_settings[bus].disable_scsi_reset =
		nv->bus[bus].config_1.scsi_reset_disable;

	/* Initiator ID. */
	ha->bus_settings[bus].id = nv->bus[bus].config_1.initiator_id;
	mb[0] = MBC_SET_INITIATOR_ID;
	mb[1] = bus ? ha->bus_settings[bus].id | BIT_7 :
		ha->bus_settings[bus].id;
	status = qla1280_mailbox_command(ha, BIT_1 | BIT_0, &mb[0]);

	/* Reset Delay. */
	ha->bus_settings[bus].bus_reset_delay =
		nv->bus[bus].bus_reset_delay;

	/* Command queue depth per device. */
	ha->bus_settings[bus].hiwat = nv->bus[bus].max_queue_depth - 1;

	/* Set target parameters. */
	for (target = 0; target < MAX_TARGETS; target++)
		status |= qla1280_config_target(ha, bus, target);

	return status;
}
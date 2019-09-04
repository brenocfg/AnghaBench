#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct nvram {TYPE_7__* bus; } ;
struct scsi_qla_host {TYPE_5__* bus_settings; struct nvram nvram; } ;
struct TYPE_14__ {int max_queue_depth; TYPE_6__* target; } ;
struct TYPE_10__ {int sync_offset; scalar_t__ lun_disable; scalar_t__ device_enable; } ;
struct TYPE_9__ {int sync_offset; scalar_t__ device_enable; } ;
struct TYPE_11__ {TYPE_3__ flags1x80; TYPE_2__ flags1x160; } ;
struct TYPE_8__ {scalar_t__ tag_queuing; } ;
struct TYPE_13__ {int sync_period; int execution_throttle; TYPE_4__ flags; TYPE_1__ parameter; } ;
struct TYPE_12__ {int qtag_enables; int device_enables; int lun_disables; } ;

/* Variables and functions */
 int BIT_0 ; 
 int BIT_7 ; 
 scalar_t__ IS_ISP1x160 (struct scsi_qla_host*) ; 
 int MAILBOX_REGISTER_COUNT ; 
 int MAX_LUNS ; 
 int MBC_SET_DEVICE_QUEUE ; 
 int MBC_SET_TARGET_PARAMETERS ; 
 int TP_AUTO_REQUEST_SENSE ; 
 int TP_DISCONNECT ; 
 int TP_PARITY ; 
 int TP_RENEGOTIATE ; 
 int TP_TAGGED_QUEUE ; 
 int TP_WIDE ; 
 int qla1280_mailbox_command (struct scsi_qla_host*,int,int*) ; 

__attribute__((used)) static int
qla1280_config_target(struct scsi_qla_host *ha, int bus, int target)
{
	struct nvram *nv = &ha->nvram;
	uint16_t mb[MAILBOX_REGISTER_COUNT];
	int status, lun;
	uint16_t flag;

	/* Set Target Parameters. */
	mb[0] = MBC_SET_TARGET_PARAMETERS;
	mb[1] = (uint16_t)((bus ? target | BIT_7 : target) << 8);

	/*
	 * Do not enable sync and ppr for the initial INQUIRY run. We
	 * enable this later if we determine the target actually
	 * supports it.
	 */
	mb[2] = (TP_RENEGOTIATE | TP_AUTO_REQUEST_SENSE | TP_TAGGED_QUEUE
		 | TP_WIDE | TP_PARITY | TP_DISCONNECT);

	if (IS_ISP1x160(ha))
		mb[3] =	nv->bus[bus].target[target].flags.flags1x160.sync_offset << 8;
	else
		mb[3] =	nv->bus[bus].target[target].flags.flags1x80.sync_offset << 8;
	mb[3] |= nv->bus[bus].target[target].sync_period;
	status = qla1280_mailbox_command(ha, 0x0f, mb);

	/* Save Tag queuing enable flag. */
	flag = (BIT_0 << target);
	if (nv->bus[bus].target[target].parameter.tag_queuing)
		ha->bus_settings[bus].qtag_enables |= flag;

	/* Save Device enable flag. */
	if (IS_ISP1x160(ha)) {
		if (nv->bus[bus].target[target].flags.flags1x160.device_enable)
			ha->bus_settings[bus].device_enables |= flag;
		ha->bus_settings[bus].lun_disables |= 0;
	} else {
		if (nv->bus[bus].target[target].flags.flags1x80.device_enable)
			ha->bus_settings[bus].device_enables |= flag;
		/* Save LUN disable flag. */
		if (nv->bus[bus].target[target].flags.flags1x80.lun_disable)
			ha->bus_settings[bus].lun_disables |= flag;
	}

	/* Set Device Queue Parameters. */
	for (lun = 0; lun < MAX_LUNS; lun++) {
		mb[0] = MBC_SET_DEVICE_QUEUE;
		mb[1] = (uint16_t)((bus ? target | BIT_7 : target) << 8);
		mb[1] |= lun;
		mb[2] = nv->bus[bus].max_queue_depth;
		mb[3] = nv->bus[bus].target[target].execution_throttle;
		status |= qla1280_mailbox_command(ha, 0x0f, mb);
	}

	return status;
}
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
struct DeviceCtlBlk {int /*<<< orphan*/  sync_offset; int /*<<< orphan*/  sync_period; int /*<<< orphan*/  target_id; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC395x_write8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_OFFSET ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_SYNC ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_TARGETID ; 
 int /*<<< orphan*/  set_xfer_rate (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 

__attribute__((used)) static inline void reprogram_regs(struct AdapterCtlBlk *acb,
		struct DeviceCtlBlk *dcb)
{
	DC395x_write8(acb, TRM_S1040_SCSI_TARGETID, dcb->target_id);
	DC395x_write8(acb, TRM_S1040_SCSI_SYNC, dcb->sync_period);
	DC395x_write8(acb, TRM_S1040_SCSI_OFFSET, dcb->sync_offset);
	set_xfer_rate(acb, dcb);
}
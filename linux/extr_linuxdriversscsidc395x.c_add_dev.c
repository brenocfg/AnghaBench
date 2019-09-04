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
typedef  int u8 ;
struct ScsiInqData {int DevType; } ;
struct DeviceCtlBlk {int dev_type; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int SCSI_DEVTYPE ; 
 int /*<<< orphan*/  disc_tagq_set (struct DeviceCtlBlk*,struct ScsiInqData*) ; 

__attribute__((used)) static void add_dev(struct AdapterCtlBlk *acb, struct DeviceCtlBlk *dcb,
		struct ScsiInqData *ptr)
{
	u8 bval1 = ptr->DevType & SCSI_DEVTYPE;
	dcb->dev_type = bval1;
	/* if (bval1 == TYPE_DISK || bval1 == TYPE_MOD) */
	disc_tagq_set(dcb, ptr);
}
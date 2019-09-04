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
typedef  int uchar ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;

/* Variables and functions */
 int ASC_MAX_TID ; 
 int AscGetChipSyn (int /*<<< orphan*/ ) ; 
 int AscReadChipDvcID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetBank (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscSetChipSyn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteChipDvcID (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool AscSetChipSynRegAtID(PortAddr iop_base, uchar id, uchar sdtr_data)
{
	ASC_SCSI_BIT_ID_TYPE org_id;
	int i;
	bool sta = true;

	AscSetBank(iop_base, 1);
	org_id = AscReadChipDvcID(iop_base);
	for (i = 0; i <= ASC_MAX_TID; i++) {
		if (org_id == (0x01 << i))
			break;
	}
	org_id = (ASC_SCSI_BIT_ID_TYPE) i;
	AscWriteChipDvcID(iop_base, id);
	if (AscReadChipDvcID(iop_base) == (0x01 << id)) {
		AscSetBank(iop_base, 0);
		AscSetChipSyn(iop_base, sdtr_data);
		if (AscGetChipSyn(iop_base) != sdtr_data) {
			sta = false;
		}
	} else {
		sta = false;
	}
	AscSetBank(iop_base, 1);
	AscWriteChipDvcID(iop_base, org_id);
	AscSetBank(iop_base, 0);
	return (sta);
}
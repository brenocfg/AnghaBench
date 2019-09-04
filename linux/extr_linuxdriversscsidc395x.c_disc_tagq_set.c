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
struct ScsiInqData {int Vers; int RDF; int Flags; } ;
struct DeviceCtlBlk {int dev_mode; int max_command; int /*<<< orphan*/  sync_mode; TYPE_1__* acb; } ;
struct TYPE_2__ {int tag_max_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  EN_TAG_QUEUEING ; 
 int NTC_DO_TAG_QUEUEING ; 
 int SCSI_INQ_CMDQUEUE ; 
 int /*<<< orphan*/  tagq_blacklist (char*) ; 

__attribute__((used)) static void disc_tagq_set(struct DeviceCtlBlk *dcb, struct ScsiInqData *ptr)
{
	/* Check for SCSI format (ANSI and Response data format) */
	if ((ptr->Vers & 0x07) >= 2 || (ptr->RDF & 0x0F) == 2) {
		if ((ptr->Flags & SCSI_INQ_CMDQUEUE)
		    && (dcb->dev_mode & NTC_DO_TAG_QUEUEING) &&
		    /*(dcb->dev_mode & NTC_DO_DISCONNECT) */
		    /* ((dcb->dev_type == TYPE_DISK) 
		       || (dcb->dev_type == TYPE_MOD)) && */
		    !tagq_blacklist(((char *)ptr) + 8)) {
			if (dcb->max_command == 1)
				dcb->max_command =
				    dcb->acb->tag_max_num;
			dcb->sync_mode |= EN_TAG_QUEUEING;
			/*dcb->tag_mask = 0; */
		} else
			dcb->max_command = 1;
	}
}
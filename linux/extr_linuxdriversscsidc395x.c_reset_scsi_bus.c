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
struct AdapterCtlBlk {int /*<<< orphan*/  acb_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_RSTSCSI ; 
 int INT_SCSIRESET ; 
 int /*<<< orphan*/  RESET_DEV ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_INTSTATUS ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,struct AdapterCtlBlk*) ; 

__attribute__((used)) static void reset_scsi_bus(struct AdapterCtlBlk *acb)
{
	dprintkdbg(DBG_0, "reset_scsi_bus: acb=%p\n", acb);
	acb->acb_flag |= RESET_DEV;	/* RESET_DETECT, RESET_DONE, RESET_DEV */
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_RSTSCSI);

	while (!(DC395x_read8(acb, TRM_S1040_SCSI_INTSTATUS) & INT_SCSIRESET))
		/* nothing */;
}
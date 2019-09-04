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
typedef  int /*<<< orphan*/  u16 ;
struct ScsiReqBlk {int /*<<< orphan*/  cmd; } ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int /*<<< orphan*/  DC395x_write16 (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_DATALATCH ; 
 int /*<<< orphan*/  TRM_S1040_SCSI_CONTROL ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void command_phase0(struct AdapterCtlBlk *acb, struct ScsiReqBlk *srb,
		u16 *pscsi_status)
{
	dprintkdbg(DBG_0, "command_phase0: (0x%p)\n", srb->cmd);
	DC395x_write16(acb, TRM_S1040_SCSI_CONTROL, DO_DATALATCH);
}
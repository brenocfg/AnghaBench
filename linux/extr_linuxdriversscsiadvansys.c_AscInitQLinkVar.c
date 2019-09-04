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
typedef  int ushort ;
typedef  scalar_t__ uchar ;
struct TYPE_3__ {scalar_t__ max_total_qng; int /*<<< orphan*/  iop_base; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ ASC_DVC_VAR ;

/* Variables and functions */
 int ASCV_ASCDVC_ERR_CODE_W ; 
 int ASCV_BUSY_QHEAD_B ; 
 int ASCV_DISC1_QHEAD_B ; 
 int ASCV_HALTCODE_W ; 
 int ASCV_SCSIBUSY_B ; 
 int ASCV_STOP_CODE_B ; 
 scalar_t__ ASCV_TOTAL_READY_Q_B ; 
 int ASCV_WTM_FLAG_B ; 
 int ASC_QADR_BEG ; 
 int /*<<< orphan*/  AscPutQDoneInProgress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscPutRiscVarDoneQTail (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscPutRiscVarFreeQHead (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscPutVarDoneQTail (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscPutVarFreeQHead (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AscInitQLinkVar(ASC_DVC_VAR *asc_dvc)
{
	PortAddr iop_base;
	int i;
	ushort lram_addr;

	iop_base = asc_dvc->iop_base;
	AscPutRiscVarFreeQHead(iop_base, 1);
	AscPutRiscVarDoneQTail(iop_base, asc_dvc->max_total_qng);
	AscPutVarFreeQHead(iop_base, 1);
	AscPutVarDoneQTail(iop_base, asc_dvc->max_total_qng);
	AscWriteLramByte(iop_base, ASCV_BUSY_QHEAD_B,
			 (uchar)((int)asc_dvc->max_total_qng + 1));
	AscWriteLramByte(iop_base, ASCV_DISC1_QHEAD_B,
			 (uchar)((int)asc_dvc->max_total_qng + 2));
	AscWriteLramByte(iop_base, (ushort)ASCV_TOTAL_READY_Q_B,
			 asc_dvc->max_total_qng);
	AscWriteLramWord(iop_base, ASCV_ASCDVC_ERR_CODE_W, 0);
	AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
	AscWriteLramByte(iop_base, ASCV_STOP_CODE_B, 0);
	AscWriteLramByte(iop_base, ASCV_SCSIBUSY_B, 0);
	AscWriteLramByte(iop_base, ASCV_WTM_FLAG_B, 0);
	AscPutQDoneInProgress(iop_base, 0);
	lram_addr = ASC_QADR_BEG;
	for (i = 0; i < 32; i++, lram_addr += 2) {
		AscWriteLramWord(iop_base, lram_addr, 0);
	}
}
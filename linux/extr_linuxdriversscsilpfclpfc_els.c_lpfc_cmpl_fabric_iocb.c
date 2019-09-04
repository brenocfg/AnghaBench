#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lsRjtRsnCode; } ;
struct TYPE_8__ {TYPE_3__ b; int /*<<< orphan*/  lsRjtError; } ;
struct ls_rjt {TYPE_4__ un; } ;
struct TYPE_5__ {int* ulpWord; } ;
struct TYPE_6__ {int ulpStatus; TYPE_1__ un; } ;
struct lpfc_iocbq {int iocb_flag; int /*<<< orphan*/  (* iocb_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ;int /*<<< orphan*/  (* fabric_iocb_cmpl ) (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ;TYPE_2__ iocb; } ;
struct lpfc_hba {int /*<<< orphan*/  bit_flags; int /*<<< orphan*/  fabric_iocb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  FABRIC_COMANDS_BLOCKED ; 
#define  IOSTAT_FABRIC_BSY 132 
#define  IOSTAT_FABRIC_RJT 131 
#define  IOSTAT_LS_RJT 130 
#define  IOSTAT_NPORT_BSY 129 
#define  IOSTAT_NPORT_RJT 128 
 int LPFC_IO_FABRIC ; 
 int /*<<< orphan*/  LSRJT_LOGICAL_BSY ; 
 int /*<<< orphan*/  LSRJT_UNABLE_TPC ; 
 int RJT_UNAVAIL_TEMP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be32_to_cpu (int) ; 
 int /*<<< orphan*/  lpfc_block_fabric_iocbs (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_resume_fabric_iocbs (struct lpfc_hba*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_hba*,struct lpfc_iocbq*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lpfc_cmpl_fabric_iocb(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
	struct lpfc_iocbq *rspiocb)
{
	struct ls_rjt stat;

	BUG_ON((cmdiocb->iocb_flag & LPFC_IO_FABRIC) != LPFC_IO_FABRIC);

	switch (rspiocb->iocb.ulpStatus) {
		case IOSTAT_NPORT_RJT:
		case IOSTAT_FABRIC_RJT:
			if (rspiocb->iocb.un.ulpWord[4] & RJT_UNAVAIL_TEMP) {
				lpfc_block_fabric_iocbs(phba);
			}
			break;

		case IOSTAT_NPORT_BSY:
		case IOSTAT_FABRIC_BSY:
			lpfc_block_fabric_iocbs(phba);
			break;

		case IOSTAT_LS_RJT:
			stat.un.lsRjtError =
				be32_to_cpu(rspiocb->iocb.un.ulpWord[4]);
			if ((stat.un.b.lsRjtRsnCode == LSRJT_UNABLE_TPC) ||
				(stat.un.b.lsRjtRsnCode == LSRJT_LOGICAL_BSY))
				lpfc_block_fabric_iocbs(phba);
			break;
	}

	BUG_ON(atomic_read(&phba->fabric_iocb_count) == 0);

	cmdiocb->iocb_cmpl = cmdiocb->fabric_iocb_cmpl;
	cmdiocb->fabric_iocb_cmpl = NULL;
	cmdiocb->iocb_flag &= ~LPFC_IO_FABRIC;
	cmdiocb->iocb_cmpl(phba, cmdiocb, rspiocb);

	atomic_dec(&phba->fabric_iocb_count);
	if (!test_bit(FABRIC_COMANDS_BLOCKED, &phba->bit_flags)) {
		/* Post any pending iocbs to HBA */
		lpfc_resume_fabric_iocbs(phba);
	}
}
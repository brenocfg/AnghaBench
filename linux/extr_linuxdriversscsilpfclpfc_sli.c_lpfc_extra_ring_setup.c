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
struct TYPE_4__ {int /*<<< orphan*/  numRiocb; int /*<<< orphan*/  numCiocb; } ;
struct TYPE_5__ {TYPE_1__ sli3; } ;
struct lpfc_sli_ring {int iotag_max; int num_mask; TYPE_3__* prt; TYPE_2__ sli; } ;
struct lpfc_sli {struct lpfc_sli_ring* sli3_ring; } ;
struct lpfc_hba {int /*<<< orphan*/  cfg_multi_ring_type; int /*<<< orphan*/  cfg_multi_ring_rctl; struct lpfc_sli sli; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lpfc_sli_rcv_unsol_event; int /*<<< orphan*/  type; int /*<<< orphan*/  rctl; scalar_t__ profile; } ;

/* Variables and functions */
 size_t LPFC_EXTRA_RING ; 
 size_t LPFC_FCP_RING ; 
 scalar_t__ SLI2_IOCB_CMD_R1XTRA_ENTRIES ; 
 scalar_t__ SLI2_IOCB_CMD_R3XTRA_ENTRIES ; 
 scalar_t__ SLI2_IOCB_RSP_R1XTRA_ENTRIES ; 
 scalar_t__ SLI2_IOCB_RSP_R3XTRA_ENTRIES ; 

__attribute__((used)) static int
lpfc_extra_ring_setup( struct lpfc_hba *phba)
{
	struct lpfc_sli *psli;
	struct lpfc_sli_ring *pring;

	psli = &phba->sli;

	/* Adjust cmd/rsp ring iocb entries more evenly */

	/* Take some away from the FCP ring */
	pring = &psli->sli3_ring[LPFC_FCP_RING];
	pring->sli.sli3.numCiocb -= SLI2_IOCB_CMD_R1XTRA_ENTRIES;
	pring->sli.sli3.numRiocb -= SLI2_IOCB_RSP_R1XTRA_ENTRIES;
	pring->sli.sli3.numCiocb -= SLI2_IOCB_CMD_R3XTRA_ENTRIES;
	pring->sli.sli3.numRiocb -= SLI2_IOCB_RSP_R3XTRA_ENTRIES;

	/* and give them to the extra ring */
	pring = &psli->sli3_ring[LPFC_EXTRA_RING];

	pring->sli.sli3.numCiocb += SLI2_IOCB_CMD_R1XTRA_ENTRIES;
	pring->sli.sli3.numRiocb += SLI2_IOCB_RSP_R1XTRA_ENTRIES;
	pring->sli.sli3.numCiocb += SLI2_IOCB_CMD_R3XTRA_ENTRIES;
	pring->sli.sli3.numRiocb += SLI2_IOCB_RSP_R3XTRA_ENTRIES;

	/* Setup default profile for this ring */
	pring->iotag_max = 4096;
	pring->num_mask = 1;
	pring->prt[0].profile = 0;      /* Mask 0 */
	pring->prt[0].rctl = phba->cfg_multi_ring_rctl;
	pring->prt[0].type = phba->cfg_multi_ring_type;
	pring->prt[0].lpfc_sli_rcv_unsol_event = NULL;
	return 0;
}
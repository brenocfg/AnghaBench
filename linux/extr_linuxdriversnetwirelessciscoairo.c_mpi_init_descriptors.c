#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int valid; int eoc; } ;
struct TYPE_13__ {TYPE_8__ rid_desc; scalar_t__ card_ram_off; } ;
struct airo_info {TYPE_3__ config_desc; TYPE_6__* dev; scalar_t__ pciaux; TYPE_2__* txfids; TYPE_1__* rxfids; } ;
typedef  int /*<<< orphan*/  rsp ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int /*<<< orphan*/  TxFid ;
struct TYPE_15__ {int /*<<< orphan*/  name; } ;
struct TYPE_14__ {int parm2; scalar_t__ parm1; int /*<<< orphan*/  parm0; void* cmd; } ;
struct TYPE_12__ {TYPE_8__ tx_desc; scalar_t__ card_ram_off; } ;
struct TYPE_11__ {TYPE_8__ rx_desc; scalar_t__ card_ram_off; } ;
typedef  int /*<<< orphan*/  RxFid ;
typedef  int /*<<< orphan*/  Rid ;
typedef  TYPE_4__ Resp ;
typedef  TYPE_4__ Cmd ;

/* Variables and functions */
 void* CMD_ALLOCATEAUX ; 
 int /*<<< orphan*/  FID_RX ; 
 int /*<<< orphan*/  FID_TX ; 
 int MPI_MAX_FIDS ; 
 int /*<<< orphan*/  RID_RW ; 
 int SUCCESS ; 
 int /*<<< orphan*/  airo_print_err (int /*<<< orphan*/ ,char*) ; 
 int issuecommand (struct airo_info*,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,TYPE_8__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_6__*) ; 

__attribute__((used)) static int mpi_init_descriptors (struct airo_info *ai)
{
	Cmd cmd;
	Resp rsp;
	int i;
	int rc = SUCCESS;

	/* Alloc  card RX descriptors */
	netif_stop_queue(ai->dev);

	memset(&rsp,0,sizeof(rsp));
	memset(&cmd,0,sizeof(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = FID_RX;
	cmd.parm1 = (ai->rxfids[0].card_ram_off - ai->pciaux);
	cmd.parm2 = MPI_MAX_FIDS;
	rc=issuecommand(ai, &cmd, &rsp);
	if (rc != SUCCESS) {
		airo_print_err(ai->dev->name, "Couldn't allocate RX FID");
		return rc;
	}

	for (i=0; i<MPI_MAX_FIDS; i++) {
		memcpy_toio(ai->rxfids[i].card_ram_off,
			&ai->rxfids[i].rx_desc, sizeof(RxFid));
	}

	/* Alloc card TX descriptors */

	memset(&rsp,0,sizeof(rsp));
	memset(&cmd,0,sizeof(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = FID_TX;
	cmd.parm1 = (ai->txfids[0].card_ram_off - ai->pciaux);
	cmd.parm2 = MPI_MAX_FIDS;

	for (i=0; i<MPI_MAX_FIDS; i++) {
		ai->txfids[i].tx_desc.valid = 1;
		memcpy_toio(ai->txfids[i].card_ram_off,
			&ai->txfids[i].tx_desc, sizeof(TxFid));
	}
	ai->txfids[i-1].tx_desc.eoc = 1; /* Last descriptor has EOC set */

	rc=issuecommand(ai, &cmd, &rsp);
	if (rc != SUCCESS) {
		airo_print_err(ai->dev->name, "Couldn't allocate TX FID");
		return rc;
	}

	/* Alloc card Rid descriptor */
	memset(&rsp,0,sizeof(rsp));
	memset(&cmd,0,sizeof(cmd));

	cmd.cmd = CMD_ALLOCATEAUX;
	cmd.parm0 = RID_RW;
	cmd.parm1 = (ai->config_desc.card_ram_off - ai->pciaux);
	cmd.parm2 = 1; /* Magic number... */
	rc=issuecommand(ai, &cmd, &rsp);
	if (rc != SUCCESS) {
		airo_print_err(ai->dev->name, "Couldn't allocate RID");
		return rc;
	}

	memcpy_toio(ai->config_desc.card_ram_off,
		&ai->config_desc.rid_desc, sizeof(Rid));

	return rc;
}
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
struct TYPE_7__ {TYPE_4__* shost; } ;
struct sas_ha_struct {unsigned short num_phys; TYPE_3__ core; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  lldd_module; int /*<<< orphan*/  dev; int /*<<< orphan*/  sas_ha_name; int /*<<< orphan*/ ** sas_port; int /*<<< orphan*/ ** sas_phy; scalar_t__ lldd_ha; } ;
struct mvs_prv_info {unsigned short n_host; struct mvs_info** mvi; } ;
struct mvs_info {int flags; TYPE_4__* shost; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  dev; TYPE_2__* port; TYPE_1__* phy; } ;
struct mvs_chip_info {int n_phy; } ;
struct Scsi_Host {int can_queue; int /*<<< orphan*/  sg_tablesize; } ;
struct TYPE_8__ {int /*<<< orphan*/  cmd_per_lun; } ;
struct TYPE_6__ {int /*<<< orphan*/  sas_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  sas_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int MVF_FLAG_SOC ; 
 int MVS_CHIP_SLOT_SZ ; 
 int /*<<< orphan*/  MVS_MAX_SG ; 
 int /*<<< orphan*/  MVS_QUEUE_SIZE ; 
 int MVS_SOC_CAN_QUEUE ; 
 int /*<<< orphan*/  SG_ALL ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u16 ; 

__attribute__((used)) static void  mvs_post_sas_ha_init(struct Scsi_Host *shost,
			const struct mvs_chip_info *chip_info)
{
	int can_queue, i = 0, j = 0;
	struct mvs_info *mvi = NULL;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	unsigned short nr_core = ((struct mvs_prv_info *)sha->lldd_ha)->n_host;

	for (j = 0; j < nr_core; j++) {
		mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[j];
		for (i = 0; i < chip_info->n_phy; i++) {
			sha->sas_phy[j * chip_info->n_phy  + i] =
				&mvi->phy[i].sas_phy;
			sha->sas_port[j * chip_info->n_phy + i] =
				&mvi->port[i].sas_port;
		}
	}

	sha->sas_ha_name = DRV_NAME;
	sha->dev = mvi->dev;
	sha->lldd_module = THIS_MODULE;
	sha->sas_addr = &mvi->sas_addr[0];

	sha->num_phys = nr_core * chip_info->n_phy;

	if (mvi->flags & MVF_FLAG_SOC)
		can_queue = MVS_SOC_CAN_QUEUE;
	else
		can_queue = MVS_CHIP_SLOT_SZ;

	shost->sg_tablesize = min_t(u16, SG_ALL, MVS_MAX_SG);
	shost->can_queue = can_queue;
	mvi->shost->cmd_per_lun = MVS_QUEUE_SIZE;
	sha->core.shost = mvi->shost;
}
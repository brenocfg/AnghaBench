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
struct sas_ha_struct {struct mvs_prv_info* lldd_ha; } ;
struct mvs_prv_info {unsigned short n_host; int scan_finished; struct mvs_info** mvi; } ;
struct mvs_info {TYPE_1__* chip; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int n_phy; } ;

/* Variables and functions */
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  mvs_bytes_dmaed (struct mvs_info*,int) ; 

void mvs_scan_start(struct Scsi_Host *shost)
{
	int i, j;
	unsigned short core_nr;
	struct mvs_info *mvi;
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct mvs_prv_info *mvs_prv = sha->lldd_ha;

	core_nr = ((struct mvs_prv_info *)sha->lldd_ha)->n_host;

	for (j = 0; j < core_nr; j++) {
		mvi = ((struct mvs_prv_info *)sha->lldd_ha)->mvi[j];
		for (i = 0; i < mvi->chip->n_phy; ++i)
			mvs_bytes_dmaed(mvi, i);
	}
	mvs_prv->scan_finished = 1;
}
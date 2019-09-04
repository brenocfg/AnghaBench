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
struct hisi_hba {TYPE_1__* hw; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* phys_init ) (struct hisi_hba*) ;} ;

/* Variables and functions */
 struct hisi_hba* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*) ; 

void hisi_sas_scan_start(struct Scsi_Host *shost)
{
	struct hisi_hba *hisi_hba = shost_priv(shost);

	hisi_hba->hw->phys_init(hisi_hba);
}
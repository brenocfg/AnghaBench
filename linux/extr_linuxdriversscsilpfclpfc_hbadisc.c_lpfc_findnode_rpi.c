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
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 struct lpfc_nodelist* __lpfc_findnode_rpi (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

struct lpfc_nodelist *
lpfc_findnode_rpi(struct lpfc_vport *vport, uint16_t rpi)
{
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	struct lpfc_nodelist *ndlp;

	spin_lock_irq(shost->host_lock);
	ndlp = __lpfc_findnode_rpi(vport, rpi);
	spin_unlock_irq(shost->host_lock);
	return ndlp;
}
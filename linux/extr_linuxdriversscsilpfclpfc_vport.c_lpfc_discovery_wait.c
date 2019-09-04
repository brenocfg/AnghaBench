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
typedef  int uint32_t ;
struct lpfc_vport {scalar_t__ num_disc_nodes; int fc_flag; scalar_t__ port_state; struct lpfc_hba* phba; } ;
struct lpfc_hba {int fc_ratov; } ;

/* Variables and functions */
 int FC_DISC_TMO ; 
 int FC_NDISC_ACTIVE ; 
 int FC_NLP_MORE ; 
 int FC_RSCN_DEFERRED ; 
 int FC_RSCN_DISCOVERY ; 
 int FC_RSCN_MODE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_VPORT ; 
 scalar_t__ LPFC_VPORT_FAILED ; 
 scalar_t__ LPFC_VPORT_READY ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int,scalar_t__,...) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void lpfc_discovery_wait(struct lpfc_vport *vport)
{
	struct lpfc_hba *phba = vport->phba;
	uint32_t wait_flags = 0;
	unsigned long wait_time_max;
	unsigned long start_time;

	wait_flags = FC_RSCN_MODE | FC_RSCN_DISCOVERY | FC_NLP_MORE |
		     FC_RSCN_DEFERRED | FC_NDISC_ACTIVE | FC_DISC_TMO;

	/*
	 * The time constraint on this loop is a balance between the
	 * fabric RA_TOV value and dev_loss tmo.  The driver's
	 * devloss_tmo is 10 giving this loop a 3x multiplier minimally.
	 */
	wait_time_max = msecs_to_jiffies(((phba->fc_ratov * 3) + 3) * 1000);
	wait_time_max += jiffies;
	start_time = jiffies;
	while (time_before(jiffies, wait_time_max)) {
		if ((vport->num_disc_nodes > 0)    ||
		    (vport->fc_flag & wait_flags)  ||
		    ((vport->port_state > LPFC_VPORT_FAILED) &&
		     (vport->port_state < LPFC_VPORT_READY))) {
			lpfc_printf_vlog(vport, KERN_INFO, LOG_VPORT,
					"1833 Vport discovery quiesce Wait:"
					" state x%x fc_flags x%x"
					" num_nodes x%x, waiting 1000 msecs"
					" total wait msecs x%x\n",
					vport->port_state, vport->fc_flag,
					vport->num_disc_nodes,
					jiffies_to_msecs(jiffies - start_time));
			msleep(1000);
		} else {
			/* Base case.  Wait variants satisfied.  Break out */
			lpfc_printf_vlog(vport, KERN_INFO, LOG_VPORT,
					 "1834 Vport discovery quiesced:"
					 " state x%x fc_flags x%x"
					 " wait msecs x%x\n",
					 vport->port_state, vport->fc_flag,
					 jiffies_to_msecs(jiffies
						- start_time));
			break;
		}
	}

	if (time_after(jiffies, wait_time_max))
		lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
				"1835 Vport discovery quiesce failed:"
				" state x%x fc_flags x%x wait msecs x%x\n",
				vport->port_state, vport->fc_flag,
				jiffies_to_msecs(jiffies - start_time));
}
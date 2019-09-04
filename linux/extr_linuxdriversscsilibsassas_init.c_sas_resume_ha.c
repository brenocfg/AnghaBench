#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  shost; } ;
struct sas_ha_struct {int num_phys; TYPE_2__ core; struct asd_sas_phy** sas_phy; int /*<<< orphan*/  eh_wait_q; int /*<<< orphan*/  dev; } ;
struct asd_sas_phy {TYPE_1__* phy; scalar_t__ suspended; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHYE_RESUME_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 unsigned long msecs_to_jiffies (int) ; 
 int phys_suspended (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_drain_work (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  sas_notify_phy_event (struct asd_sas_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long const) ; 

void sas_resume_ha(struct sas_ha_struct *ha)
{
	const unsigned long tmo = msecs_to_jiffies(25000);
	int i;

	/* deform ports on phys that did not resume
	 * at this point we may be racing the phy coming back (as posted
	 * by the lldd).  So we post the event and once we are in the
	 * libsas context check that the phy remains suspended before
	 * tearing it down.
	 */
	i = phys_suspended(ha);
	if (i)
		dev_info(ha->dev, "waiting up to 25 seconds for %d phy%s to resume\n",
			 i, i > 1 ? "s" : "");
	wait_event_timeout(ha->eh_wait_q, phys_suspended(ha) == 0, tmo);
	for (i = 0; i < ha->num_phys; i++) {
		struct asd_sas_phy *phy = ha->sas_phy[i];

		if (phy->suspended) {
			dev_warn(&phy->phy->dev, "resume timeout\n");
			sas_notify_phy_event(phy, PHYE_RESUME_TIMEOUT);
		}
	}

	/* all phys are back up or timed out, turn on i/o so we can
	 * flush out disks that did not return
	 */
	scsi_unblock_requests(ha->core.shost);
	sas_drain_work(ha);
}
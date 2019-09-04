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
struct work_struct {int dummy; } ;
struct asd_sas_phy {scalar_t__ suspended; scalar_t__ error; TYPE_1__* phy; } ;
struct asd_sas_event {struct asd_sas_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sas_deform_port (struct asd_sas_phy*,int) ; 
 struct asd_sas_event* to_asd_sas_event (struct work_struct*) ; 

__attribute__((used)) static void sas_phye_resume_timeout(struct work_struct *work)
{
	struct asd_sas_event *ev = to_asd_sas_event(work);
	struct asd_sas_phy *phy = ev->phy;

	/* phew, lldd got the phy back in the nick of time */
	if (!phy->suspended) {
		dev_info(&phy->phy->dev, "resume timeout cancelled\n");
		return;
	}

	phy->error = 0;
	phy->suspended = 0;
	sas_deform_port(phy, 1);
}
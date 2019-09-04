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
struct sas_ha_struct {int dummy; } ;
struct asd_sas_phy {struct sas_ha_struct* ha; } ;
struct asd_sas_event {int /*<<< orphan*/  work; } ;
typedef  enum phy_event { ____Placeholder_phy_event } phy_event ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_SAS_EVENT (struct asd_sas_event*,int /*<<< orphan*/ ,struct asd_sas_phy*,int) ; 
 int PHY_NUM_EVENTS ; 
 struct asd_sas_event* sas_alloc_event (struct asd_sas_phy*) ; 
 int /*<<< orphan*/  sas_free_event (struct asd_sas_event*) ; 
 int /*<<< orphan*/  sas_phy_event_worker ; 
 int sas_queue_event (int,int /*<<< orphan*/ *,struct sas_ha_struct*) ; 

int sas_notify_phy_event(struct asd_sas_phy *phy, enum phy_event event)
{
	struct asd_sas_event *ev;
	struct sas_ha_struct *ha = phy->ha;
	int ret;

	BUG_ON(event >= PHY_NUM_EVENTS);

	ev = sas_alloc_event(phy);
	if (!ev)
		return -ENOMEM;

	INIT_SAS_EVENT(ev, sas_phy_event_worker, phy, event);

	ret = sas_queue_event(event, &ev->work, ha);
	if (ret != 1)
		sas_free_event(ev);

	return ret;
}
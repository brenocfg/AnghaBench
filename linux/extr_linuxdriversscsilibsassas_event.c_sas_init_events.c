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
struct sas_ha_struct {int /*<<< orphan*/  notify_phy_event; int /*<<< orphan*/  notify_port_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  sas_notify_phy_event ; 
 int /*<<< orphan*/  sas_notify_port_event ; 

int sas_init_events(struct sas_ha_struct *sas_ha)
{
	sas_ha->notify_port_event = sas_notify_port_event;
	sas_ha->notify_phy_event = sas_notify_phy_event;

	return 0;
}
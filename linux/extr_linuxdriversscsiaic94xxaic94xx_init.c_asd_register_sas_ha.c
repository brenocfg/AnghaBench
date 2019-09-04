#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct asd_sas_port {int dummy; } ;
typedef  struct asd_sas_port asd_sas_phy ;
struct TYPE_6__ {char* sas_ha_name; int num_phys; struct asd_sas_port** sas_port; struct asd_sas_port** sas_phy; int /*<<< orphan*/ * sas_addr; int /*<<< orphan*/  lldd_module; } ;
struct TYPE_4__ {int /*<<< orphan*/ * sas_addr; } ;
struct asd_ha_struct {TYPE_3__ sas_ha; struct asd_sas_port* ports; TYPE_2__* phys; TYPE_1__ hw_prof; scalar_t__ name; } ;
struct TYPE_5__ {struct asd_sas_port sas_phy; } ;

/* Variables and functions */
 int ASD_MAX_PHYS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct asd_sas_port** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct asd_sas_port**) ; 
 int sas_register_ha (TYPE_3__*) ; 

__attribute__((used)) static int asd_register_sas_ha(struct asd_ha_struct *asd_ha)
{
	int i;
	struct asd_sas_phy   **sas_phys =
		kcalloc(ASD_MAX_PHYS, sizeof(*sas_phys), GFP_KERNEL);
	struct asd_sas_port  **sas_ports =
		kcalloc(ASD_MAX_PHYS, sizeof(*sas_ports), GFP_KERNEL);

	if (!sas_phys || !sas_ports) {
		kfree(sas_phys);
		kfree(sas_ports);
		return -ENOMEM;
	}

	asd_ha->sas_ha.sas_ha_name = (char *) asd_ha->name;
	asd_ha->sas_ha.lldd_module = THIS_MODULE;
	asd_ha->sas_ha.sas_addr = &asd_ha->hw_prof.sas_addr[0];

	for (i = 0; i < ASD_MAX_PHYS; i++) {
		sas_phys[i] = &asd_ha->phys[i].sas_phy;
		sas_ports[i] = &asd_ha->ports[i];
	}

	asd_ha->sas_ha.sas_phy = sas_phys;
	asd_ha->sas_ha.sas_port= sas_ports;
	asd_ha->sas_ha.num_phys= ASD_MAX_PHYS;

	return sas_register_ha(&asd_ha->sas_ha);
}
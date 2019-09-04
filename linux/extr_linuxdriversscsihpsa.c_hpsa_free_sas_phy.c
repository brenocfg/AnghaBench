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
struct sas_phy {int dummy; } ;
struct hpsa_sas_phy {int /*<<< orphan*/  phy_list_entry; scalar_t__ added_to_port; TYPE_1__* parent_port; struct sas_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct hpsa_sas_phy*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sas_phy_delete (struct sas_phy*) ; 
 int /*<<< orphan*/  sas_port_delete_phy (int /*<<< orphan*/ ,struct sas_phy*) ; 

__attribute__((used)) static void hpsa_free_sas_phy(struct hpsa_sas_phy *hpsa_sas_phy)
{
	struct sas_phy *phy = hpsa_sas_phy->phy;

	sas_port_delete_phy(hpsa_sas_phy->parent_port->port, phy);
	if (hpsa_sas_phy->added_to_port)
		list_del(&hpsa_sas_phy->phy_list_entry);
	sas_phy_delete(phy);
	kfree(hpsa_sas_phy);
}
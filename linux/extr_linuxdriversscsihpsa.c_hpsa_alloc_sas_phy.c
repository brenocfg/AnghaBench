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
struct hpsa_sas_port {int /*<<< orphan*/  next_phy_index; TYPE_1__* parent_node; } ;
struct hpsa_sas_phy {struct hpsa_sas_port* parent_port; struct sas_phy* phy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct hpsa_sas_phy*) ; 
 struct hpsa_sas_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sas_phy* sas_phy_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hpsa_sas_phy *hpsa_alloc_sas_phy(
				struct hpsa_sas_port *hpsa_sas_port)
{
	struct hpsa_sas_phy *hpsa_sas_phy;
	struct sas_phy *phy;

	hpsa_sas_phy = kzalloc(sizeof(*hpsa_sas_phy), GFP_KERNEL);
	if (!hpsa_sas_phy)
		return NULL;

	phy = sas_phy_alloc(hpsa_sas_port->parent_node->parent_dev,
		hpsa_sas_port->next_phy_index);
	if (!phy) {
		kfree(hpsa_sas_phy);
		return NULL;
	}

	hpsa_sas_port->next_phy_index++;
	hpsa_sas_phy->phy = phy;
	hpsa_sas_phy->parent_port = hpsa_sas_port;

	return hpsa_sas_phy;
}
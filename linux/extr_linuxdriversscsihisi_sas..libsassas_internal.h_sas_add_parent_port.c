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
struct expander_device {scalar_t__ parent_port; struct ex_phy* ex_phy; } ;
struct ex_phy {int /*<<< orphan*/  phy; } ;
struct domain_device {TYPE_1__* rphy; struct expander_device ex_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int sas_port_add (scalar_t__) ; 
 int /*<<< orphan*/  sas_port_add_phy (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sas_port_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sas_port_mark_backlink (scalar_t__) ; 

__attribute__((used)) static inline void sas_add_parent_port(struct domain_device *dev, int phy_id)
{
	struct expander_device *ex = &dev->ex_dev;
	struct ex_phy *ex_phy = &ex->ex_phy[phy_id];

	if (!ex->parent_port) {
		ex->parent_port = sas_port_alloc(&dev->rphy->dev, phy_id);
		/* FIXME: error handling */
		BUG_ON(!ex->parent_port);
		BUG_ON(sas_port_add(ex->parent_port));
		sas_port_mark_backlink(ex->parent_port);
	}
	sas_port_add_phy(ex->parent_port, ex_phy->phy);
}
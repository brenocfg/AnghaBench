#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  work; } ;
struct rockchip_usb2phy_port {TYPE_2__ otg_sm_work; int /*<<< orphan*/  mutex; TYPE_1__* port_cfg; TYPE_4__* phy; } ;
struct rockchip_usb2phy {int /*<<< orphan*/  grf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct TYPE_8__ {TYPE_3__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bvalid_det_clr; int /*<<< orphan*/  bvalid_det_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct rockchip_usb2phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  property_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_usb2phy_otg_sm_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rockchip_usb2phy_bvalid_irq(int irq, void *data)
{
	struct rockchip_usb2phy_port *rport = data;
	struct rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);

	if (!property_enabled(rphy->grf, &rport->port_cfg->bvalid_det_st))
		return IRQ_NONE;

	mutex_lock(&rport->mutex);

	/* clear bvalid detect irq pending status */
	property_enable(rphy->grf, &rport->port_cfg->bvalid_det_clr, true);

	mutex_unlock(&rport->mutex);

	rockchip_usb2phy_otg_sm_work(&rport->otg_sm_work.work);

	return IRQ_HANDLED;
}
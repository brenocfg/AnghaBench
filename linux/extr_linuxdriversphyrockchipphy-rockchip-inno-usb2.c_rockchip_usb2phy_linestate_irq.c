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
struct TYPE_8__ {int /*<<< orphan*/  work; } ;
struct rockchip_usb2phy_port {scalar_t__ port_id; TYPE_4__ sm_work; scalar_t__ suspended; int /*<<< orphan*/  mutex; TYPE_3__* port_cfg; TYPE_2__* phy; } ;
struct rockchip_usb2phy {int /*<<< orphan*/  grf; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  ls_det_clr; int /*<<< orphan*/  ls_det_en; int /*<<< orphan*/  ls_det_st; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ USB2PHY_PORT_HOST ; 
 struct rockchip_usb2phy* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  property_enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_usb2phy_sm_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t rockchip_usb2phy_linestate_irq(int irq, void *data)
{
	struct rockchip_usb2phy_port *rport = data;
	struct rockchip_usb2phy *rphy = dev_get_drvdata(rport->phy->dev.parent);

	if (!property_enabled(rphy->grf, &rport->port_cfg->ls_det_st))
		return IRQ_NONE;

	mutex_lock(&rport->mutex);

	/* disable linestate detect irq and clear its status */
	property_enable(rphy->grf, &rport->port_cfg->ls_det_en, false);
	property_enable(rphy->grf, &rport->port_cfg->ls_det_clr, true);

	mutex_unlock(&rport->mutex);

	/*
	 * In this case for host phy port, a new device is plugged in,
	 * meanwhile, if the phy port is suspended, we need rearm the work to
	 * resume it and mange its states; otherwise, we do nothing about that.
	 */
	if (rport->suspended && rport->port_id == USB2PHY_PORT_HOST)
		rockchip_usb2phy_sm_work(&rport->sm_work.work);

	return IRQ_HANDLED;
}
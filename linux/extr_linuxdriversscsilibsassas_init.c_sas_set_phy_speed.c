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
struct sas_rphy {int dummy; } ;
struct sas_phy_linkrates {scalar_t__ minimum_linkrate; scalar_t__ maximum_linkrate; } ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct sas_phy {scalar_t__ maximum_linkrate; scalar_t__ minimum_linkrate; scalar_t__ minimum_linkrate_hw; scalar_t__ maximum_linkrate_hw; size_t number; TYPE_4__ dev; } ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_6__ {TYPE_1__* shost; } ;
struct sas_ha_struct {TYPE_2__ core; struct asd_sas_phy** sas_phy; } ;
struct domain_device {int dummy; } ;
struct asd_sas_phy {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {int (* lldd_control_phy ) (struct asd_sas_phy*,int /*<<< orphan*/ ,struct sas_phy_linkrates*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PHY_FUNC_LINK_RESET ; 
 int /*<<< orphan*/  PHY_FUNC_SET_LINK_RATE ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 struct sas_rphy* dev_to_rphy (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* dev_to_shost (int /*<<< orphan*/ ) ; 
 struct domain_device* sas_find_dev_by_rphy (struct sas_rphy*) ; 
 int sas_smp_phy_control (struct domain_device*,size_t,int /*<<< orphan*/ ,struct sas_phy_linkrates*) ; 
 scalar_t__ scsi_is_sas_phy_local (struct sas_phy*) ; 
 int stub1 (struct asd_sas_phy*,int /*<<< orphan*/ ,struct sas_phy_linkrates*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

int sas_set_phy_speed(struct sas_phy *phy,
		      struct sas_phy_linkrates *rates)
{
	int ret;

	if ((rates->minimum_linkrate &&
	     rates->minimum_linkrate > phy->maximum_linkrate) ||
	    (rates->maximum_linkrate &&
	     rates->maximum_linkrate < phy->minimum_linkrate))
		return -EINVAL;

	if (rates->minimum_linkrate &&
	    rates->minimum_linkrate < phy->minimum_linkrate_hw)
		rates->minimum_linkrate = phy->minimum_linkrate_hw;

	if (rates->maximum_linkrate &&
	    rates->maximum_linkrate > phy->maximum_linkrate_hw)
		rates->maximum_linkrate = phy->maximum_linkrate_hw;

	if (scsi_is_sas_phy_local(phy)) {
		struct Scsi_Host *shost = dev_to_shost(phy->dev.parent);
		struct sas_ha_struct *sas_ha = SHOST_TO_SAS_HA(shost);
		struct asd_sas_phy *asd_phy = sas_ha->sas_phy[phy->number];
		struct sas_internal *i =
			to_sas_internal(sas_ha->core.shost->transportt);

		ret = i->dft->lldd_control_phy(asd_phy, PHY_FUNC_SET_LINK_RATE,
					       rates);
	} else {
		struct sas_rphy *rphy = dev_to_rphy(phy->dev.parent);
		struct domain_device *ddev = sas_find_dev_by_rphy(rphy);
		ret = sas_smp_phy_control(ddev, phy->number,
					  PHY_FUNC_LINK_RESET, rates);

	}

	return ret;
}
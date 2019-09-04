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
typedef  size_t u8 ;
struct sas_phy_linkrates {int minimum_linkrate; int maximum_linkrate; } ;
struct sas_internal {TYPE_3__* dft; } ;
struct TYPE_5__ {TYPE_1__* shost; } ;
struct sas_ha_struct {size_t num_phys; struct asd_sas_phy** sas_phy; TYPE_2__ core; } ;
struct asd_sas_phy {int dummy; } ;
typedef  enum sas_linkrate { ____Placeholder_sas_linkrate } sas_linkrate ;
struct TYPE_6__ {scalar_t__ (* lldd_control_phy ) (struct asd_sas_phy*,size_t,struct sas_phy_linkrates*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
#define  PHY_FUNC_CLEAR_AFFIL 134 
#define  PHY_FUNC_CLEAR_ERROR_LOG 133 
#define  PHY_FUNC_DISABLE 132 
#define  PHY_FUNC_HARD_RESET 131 
#define  PHY_FUNC_LINK_RESET 130 
#define  PHY_FUNC_NOP 129 
#define  PHY_FUNC_TX_SATA_PS_SIGNAL 128 
 size_t SMP_RESP_FUNC_ACC ; 
 size_t SMP_RESP_FUNC_FAILED ; 
 size_t SMP_RESP_NO_PHY ; 
 size_t SMP_RESP_PHY_UNK_OP ; 
 scalar_t__ sas_try_ata_reset (struct asd_sas_phy*) ; 
 scalar_t__ stub1 (struct asd_sas_phy*,size_t,struct sas_phy_linkrates*) ; 
 struct sas_internal* to_sas_internal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_phy_control(struct sas_ha_struct *sas_ha, u8 phy_id,
			    u8 phy_op, enum sas_linkrate min,
			    enum sas_linkrate max, u8 *resp_data)
{
	struct sas_internal *i =
		to_sas_internal(sas_ha->core.shost->transportt);
	struct sas_phy_linkrates rates;
	struct asd_sas_phy *asd_phy;

	if (phy_id >= sas_ha->num_phys) {
		resp_data[2] = SMP_RESP_NO_PHY;
		return;
	}

	asd_phy = sas_ha->sas_phy[phy_id];
	switch (phy_op) {
	case PHY_FUNC_NOP:
	case PHY_FUNC_LINK_RESET:
	case PHY_FUNC_HARD_RESET:
	case PHY_FUNC_DISABLE:
	case PHY_FUNC_CLEAR_ERROR_LOG:
	case PHY_FUNC_CLEAR_AFFIL:
	case PHY_FUNC_TX_SATA_PS_SIGNAL:
		break;

	default:
		resp_data[2] = SMP_RESP_PHY_UNK_OP;
		return;
	}

	rates.minimum_linkrate = min;
	rates.maximum_linkrate = max;

	/* filter reset requests through libata eh */
	if (phy_op == PHY_FUNC_LINK_RESET && sas_try_ata_reset(asd_phy) == 0) {
		resp_data[2] = SMP_RESP_FUNC_ACC;
		return;
	}

	if (i->dft->lldd_control_phy(asd_phy, phy_op, &rates))
		resp_data[2] = SMP_RESP_FUNC_FAILED;
	else
		resp_data[2] = SMP_RESP_FUNC_ACC;
}
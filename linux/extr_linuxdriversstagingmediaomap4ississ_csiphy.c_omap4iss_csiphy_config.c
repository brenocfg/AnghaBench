#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct TYPE_11__ {int pol; int pos; } ;
struct iss_csiphy_lanes_cfg {TYPE_5__ clk; TYPE_4__* data; } ;
struct TYPE_8__ {struct iss_csiphy_lanes_cfg lanecfg; } ;
struct TYPE_9__ {TYPE_2__ csi2; } ;
struct iss_v4l2_subdevs_group {scalar_t__ interface; TYPE_3__ bus; } ;
struct iss_pipeline {int external_rate; int external_bpp; TYPE_1__* external; } ;
struct iss_device {int /*<<< orphan*/  syscon; } ;
struct iss_csiphy_dphy_cfg {int /*<<< orphan*/  tclk_settle; int /*<<< orphan*/  tclk_miss; int /*<<< orphan*/  tclk_term; void* ths_settle; void* ths_term; } ;
struct iss_csi2_device {TYPE_6__* phy; } ;
struct TYPE_12__ {int used_data_lanes; unsigned int max_data_lanes; int /*<<< orphan*/  mutex; struct iss_csiphy_lanes_cfg lanes; struct iss_csiphy_dphy_cfg dphy; } ;
struct TYPE_10__ {int pos; int pol; } ;
struct TYPE_7__ {struct iss_v4l2_subdevs_group* host_priv; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 scalar_t__ ISS_INTERFACE_CSI2A_PHY1 ; 
 scalar_t__ ISS_INTERFACE_CSI2B_PHY2 ; 
 int OMAP4_CAMERARX_CSI21_CAMMODE_MASK ; 
 int OMAP4_CAMERARX_CSI21_CTRLCLKEN_MASK ; 
 int OMAP4_CAMERARX_CSI21_LANEENABLE_MASK ; 
 int OMAP4_CAMERARX_CSI21_LANEENABLE_SHIFT ; 
 int OMAP4_CAMERARX_CSI22_CAMMODE_MASK ; 
 int OMAP4_CAMERARX_CSI22_CTRLCLKEN_MASK ; 
 int OMAP4_CAMERARX_CSI22_LANEENABLE_MASK ; 
 int OMAP4_CAMERARX_CSI22_LANEENABLE_SHIFT ; 
 int /*<<< orphan*/  TCLK_MISS ; 
 int /*<<< orphan*/  TCLK_SETTLE ; 
 int /*<<< orphan*/  TCLK_TERM ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int,int) ; 
 struct iss_pipeline* to_iss_pipeline (int /*<<< orphan*/ *) ; 
 struct iss_csi2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int omap4iss_csiphy_config(struct iss_device *iss,
			   struct v4l2_subdev *csi2_subdev)
{
	struct iss_csi2_device *csi2 = v4l2_get_subdevdata(csi2_subdev);
	struct iss_pipeline *pipe = to_iss_pipeline(&csi2_subdev->entity);
	struct iss_v4l2_subdevs_group *subdevs = pipe->external->host_priv;
	struct iss_csiphy_dphy_cfg csi2phy;
	int csi2_ddrclk_khz;
	struct iss_csiphy_lanes_cfg *lanes;
	unsigned int used_lanes = 0;
	u32 cam_rx_ctrl;
	unsigned int i;

	lanes = &subdevs->bus.csi2.lanecfg;

	/*
	 * SCM.CONTROL_CAMERA_RX
	 * - bit [31] : CSIPHY2 lane 2 enable (4460+ only)
	 * - bit [30:29] : CSIPHY2 per-lane enable (1 to 0)
	 * - bit [28:24] : CSIPHY1 per-lane enable (4 to 0)
	 * - bit [21] : CSIPHY2 CTRLCLK enable
	 * - bit [20:19] : CSIPHY2 config: 00 d-phy, 01/10 ccp2
	 * - bit [18] : CSIPHY1 CTRLCLK enable
	 * - bit [17:16] : CSIPHY1 config: 00 d-phy, 01/10 ccp2
	 */
	/*
	 * TODO: When implementing DT support specify the CONTROL_CAMERA_RX
	 * register offset in the syscon property instead of hardcoding it.
	 */
	regmap_read(iss->syscon, 0x68, &cam_rx_ctrl);

	if (subdevs->interface == ISS_INTERFACE_CSI2A_PHY1) {
		cam_rx_ctrl &= ~(OMAP4_CAMERARX_CSI21_LANEENABLE_MASK |
				OMAP4_CAMERARX_CSI21_CAMMODE_MASK);
		/* NOTE: Leave CSIPHY1 config to 0x0: D-PHY mode */
		/* Enable all lanes for now */
		cam_rx_ctrl |=
			0x1f << OMAP4_CAMERARX_CSI21_LANEENABLE_SHIFT;
		/* Enable CTRLCLK */
		cam_rx_ctrl |= OMAP4_CAMERARX_CSI21_CTRLCLKEN_MASK;
	}

	if (subdevs->interface == ISS_INTERFACE_CSI2B_PHY2) {
		cam_rx_ctrl &= ~(OMAP4_CAMERARX_CSI22_LANEENABLE_MASK |
				OMAP4_CAMERARX_CSI22_CAMMODE_MASK);
		/* NOTE: Leave CSIPHY2 config to 0x0: D-PHY mode */
		/* Enable all lanes for now */
		cam_rx_ctrl |=
			0x3 << OMAP4_CAMERARX_CSI22_LANEENABLE_SHIFT;
		/* Enable CTRLCLK */
		cam_rx_ctrl |= OMAP4_CAMERARX_CSI22_CTRLCLKEN_MASK;
	}

	regmap_write(iss->syscon, 0x68, cam_rx_ctrl);

	/* Reset used lane count */
	csi2->phy->used_data_lanes = 0;

	/* Clock and data lanes verification */
	for (i = 0; i < csi2->phy->max_data_lanes; i++) {
		if (lanes->data[i].pos == 0)
			continue;

		if (lanes->data[i].pol > 1 ||
		    lanes->data[i].pos > (csi2->phy->max_data_lanes + 1))
			return -EINVAL;

		if (used_lanes & (1 << lanes->data[i].pos))
			return -EINVAL;

		used_lanes |= 1 << lanes->data[i].pos;
		csi2->phy->used_data_lanes++;
	}

	if (lanes->clk.pol > 1 ||
	    lanes->clk.pos > (csi2->phy->max_data_lanes + 1))
		return -EINVAL;

	if (lanes->clk.pos == 0 || used_lanes & (1 << lanes->clk.pos))
		return -EINVAL;

	csi2_ddrclk_khz = pipe->external_rate / 1000
		/ (2 * csi2->phy->used_data_lanes)
		* pipe->external_bpp;

	/*
	 * THS_TERM: Programmed value = ceil(12.5 ns/DDRClk period) - 1.
	 * THS_SETTLE: Programmed value = ceil(90 ns/DDRClk period) + 3.
	 */
	csi2phy.ths_term = DIV_ROUND_UP(25 * csi2_ddrclk_khz, 2000000) - 1;
	csi2phy.ths_settle = DIV_ROUND_UP(90 * csi2_ddrclk_khz, 1000000) + 3;
	csi2phy.tclk_term = TCLK_TERM;
	csi2phy.tclk_miss = TCLK_MISS;
	csi2phy.tclk_settle = TCLK_SETTLE;

	mutex_lock(&csi2->phy->mutex);
	csi2->phy->dphy = csi2phy;
	csi2->phy->lanes = *lanes;
	mutex_unlock(&csi2->phy->mutex);

	return 0;
}
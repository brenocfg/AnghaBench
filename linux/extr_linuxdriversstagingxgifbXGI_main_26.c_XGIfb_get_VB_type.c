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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  P3d4; } ;
struct xgifb_video_info {int /*<<< orphan*/  hasVB; TYPE_1__ dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASVB_LVDS ; 
 int /*<<< orphan*/  HASVB_LVDS_CHRONTEL ; 
 int /*<<< orphan*/  IND_XGI_SCRATCH_REG_CR37 ; 
#define  SIS_EXTERNAL_CHIP_LVDS 129 
#define  SIS_EXTERNAL_CHIP_LVDS_CHRONTEL 128 
 int SIS_EXTERNAL_CHIP_MASK ; 
 int /*<<< orphan*/  XGIfb_has_VB (struct xgifb_video_info*) ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void XGIfb_get_VB_type(struct xgifb_video_info *xgifb_info)
{
	u8 reg;

	if (!XGIfb_has_VB(xgifb_info)) {
		reg = xgifb_reg_get(xgifb_info->dev_info.P3d4,
				    IND_XGI_SCRATCH_REG_CR37);
		switch ((reg & SIS_EXTERNAL_CHIP_MASK) >> 1) {
		case SIS_EXTERNAL_CHIP_LVDS:
			xgifb_info->hasVB = HASVB_LVDS;
			break;
		case SIS_EXTERNAL_CHIP_LVDS_CHRONTEL:
			xgifb_info->hasVB = HASVB_LVDS_CHRONTEL;
			break;
		default:
			break;
		}
	}
}
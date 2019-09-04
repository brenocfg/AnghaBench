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
struct TYPE_2__ {int /*<<< orphan*/  Part4Port; } ;
struct xgifb_video_info {int /*<<< orphan*/  hasVB; TYPE_1__ dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASVB_301 ; 
 int /*<<< orphan*/  HASVB_302 ; 
 int /*<<< orphan*/  HASVB_NONE ; 
 int xgifb_reg_get (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool XGIfb_has_VB(struct xgifb_video_info *xgifb_info)
{
	u8 vb_chipid;

	vb_chipid = xgifb_reg_get(xgifb_info->dev_info.Part4Port, 0x00);
	switch (vb_chipid) {
	case 0x01:
		xgifb_info->hasVB = HASVB_301;
		break;
	case 0x02:
		xgifb_info->hasVB = HASVB_302;
		break;
	default:
		xgifb_info->hasVB = HASVB_NONE;
		return false;
	}
	return true;
}
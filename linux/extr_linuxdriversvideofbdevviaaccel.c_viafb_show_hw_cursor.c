#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct viafb_par {int iga_path; TYPE_2__* shared; } ;
struct fb_info {struct viafb_par* par; } ;
struct TYPE_4__ {TYPE_1__* vdev; } ;
struct TYPE_3__ {scalar_t__ engine_mmio; } ;

/* Variables and functions */
#define  HW_Cursor_OFF 131 
#define  HW_Cursor_ON 130 
#define  IGA1 129 
#define  IGA2 128 
 scalar_t__ VIA_REG_CURSOR_MODE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void viafb_show_hw_cursor(struct fb_info *info, int Status)
{
	struct viafb_par *viapar = info->par;
	u32 temp, iga_path = viapar->iga_path;

	temp = readl(viapar->shared->vdev->engine_mmio + VIA_REG_CURSOR_MODE);
	switch (Status) {
	case HW_Cursor_ON:
		temp |= 0x1;
		break;
	case HW_Cursor_OFF:
		temp &= 0xFFFFFFFE;
		break;
	}
	switch (iga_path) {
	case IGA2:
		temp |= 0x80000000;
		break;
	case IGA1:
	default:
		temp &= 0x7FFFFFFF;
	}
	writel(temp, viapar->shared->vdev->engine_mmio + VIA_REG_CURSOR_MODE);
}
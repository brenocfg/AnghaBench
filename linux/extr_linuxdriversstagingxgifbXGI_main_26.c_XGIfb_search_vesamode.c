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
struct xgifb_video_info {int mode_idx; } ;
struct TYPE_2__ {scalar_t__ mode_no; unsigned int vesa_mode_no_1; unsigned int vesa_mode_no_2; } ;

/* Variables and functions */
 TYPE_1__* XGIbios_mode ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 

__attribute__((used)) static void XGIfb_search_vesamode(struct xgifb_video_info *xgifb_info,
				  unsigned int vesamode)
{
	int i = 0;

	if (vesamode == 0)
		goto invalid;

	vesamode &= 0x1dff; /* Clean VESA mode number from other flags */

	while (XGIbios_mode[i].mode_no != 0) {
		if ((XGIbios_mode[i].vesa_mode_no_1 == vesamode) ||
		    (XGIbios_mode[i].vesa_mode_no_2 == vesamode)) {
			xgifb_info->mode_idx = i;
			return;
		}
		i++;
	}

invalid:
	pr_info("Invalid VESA mode 0x%x'\n", vesamode);
}
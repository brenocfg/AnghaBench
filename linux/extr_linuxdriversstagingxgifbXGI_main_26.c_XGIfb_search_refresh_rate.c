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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct xgifb_video_info {size_t mode_idx; int rate_idx; unsigned int refresh_rate; } ;
struct TYPE_4__ {scalar_t__ xres; scalar_t__ yres; } ;
struct TYPE_3__ {int idx; scalar_t__ xres; scalar_t__ yres; unsigned int refresh; } ;

/* Variables and functions */
 TYPE_2__* XGIbios_mode ; 
 TYPE_1__* XGIfb_vrate ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u8 XGIfb_search_refresh_rate(struct xgifb_video_info *xgifb_info,
				    unsigned int rate)
{
	u16 xres, yres;
	int i = 0;

	xres = XGIbios_mode[xgifb_info->mode_idx].xres;
	yres = XGIbios_mode[xgifb_info->mode_idx].yres;

	xgifb_info->rate_idx = 0;

	while (XGIfb_vrate[i].idx != 0 && XGIfb_vrate[i].xres <= xres) {
		/* Skip values with xres or yres less than specified */
		if ((XGIfb_vrate[i].yres != yres) ||
		    (XGIfb_vrate[i].xres != xres)) {
			i++;
			continue;
		}
		if (XGIfb_vrate[i].refresh == rate) {
			xgifb_info->rate_idx = XGIfb_vrate[i].idx;
			break;
		} else if (XGIfb_vrate[i].refresh > rate) {
			if (XGIfb_vrate[i].refresh - rate <= 3) {
				pr_debug("Adjusting rate from %d up to %d\n",
					rate, XGIfb_vrate[i].refresh);
				xgifb_info->rate_idx = XGIfb_vrate[i].idx;
				xgifb_info->refresh_rate =
					XGIfb_vrate[i].refresh;
			} else if ((XGIfb_vrate[i].idx != 1) &&
				   (rate - XGIfb_vrate[i - 1].refresh <= 2)) {
				pr_debug("Adjusting rate from %d down to %d\n",
					rate, XGIfb_vrate[i - 1].refresh);
				xgifb_info->rate_idx = XGIfb_vrate[i - 1].idx;
				xgifb_info->refresh_rate =
					XGIfb_vrate[i - 1].refresh;
			}
			break;
		} else if (rate - XGIfb_vrate[i].refresh <= 2) {
			pr_debug("Adjusting rate from %d down to %d\n",
				rate, XGIfb_vrate[i].refresh);
			xgifb_info->rate_idx = XGIfb_vrate[i].idx;
			break;
		}
		i++;
	}

	if (xgifb_info->rate_idx > 0)
		return xgifb_info->rate_idx;
	pr_info("Unsupported rate %d for %dx%d\n",
		rate, xres, yres);
	return 0;
}
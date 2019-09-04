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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
struct TYPE_2__ {unsigned long tv_pclk_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_DIVISORo (int) ; 
 int FLD_GET (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ dispc ; 
 unsigned long dispc_mgr_lclk_rate (int) ; 
 int /*<<< orphan*/  dispc_read_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ dss_mgr_is_lcd (int) ; 

__attribute__((used)) static unsigned long dispc_mgr_pclk_rate(enum omap_channel channel)
{
	unsigned long r;

	if (dss_mgr_is_lcd(channel)) {
		int pcd;
		u32 l;

		l = dispc_read_reg(DISPC_DIVISORo(channel));

		pcd = FLD_GET(l, 7, 0);

		r = dispc_mgr_lclk_rate(channel);

		return r / pcd;
	} else {
		return dispc.tv_pclk_rate;
	}
}
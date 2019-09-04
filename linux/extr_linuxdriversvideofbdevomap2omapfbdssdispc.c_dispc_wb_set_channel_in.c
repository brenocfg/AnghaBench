#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;
typedef  enum dss_writeback_channel { ____Placeholder_dss_writeback_channel } dss_writeback_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int OMAP_DSS_WB ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 

void dispc_wb_set_channel_in(enum dss_writeback_channel channel)
{
	enum omap_plane plane = OMAP_DSS_WB;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), channel, 18, 16);
}
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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  DISPC_MGR_FLD_GO ; 
 int mgr_fld_read (int,int /*<<< orphan*/ ) ; 

bool dispc_mgr_go_busy(enum omap_channel channel)
{
	return mgr_fld_read(channel, DISPC_MGR_FLD_GO) == 1;
}
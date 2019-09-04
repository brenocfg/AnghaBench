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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int OMAP_DSS_GFX ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void dispc_ovl_set_mflag(enum omap_plane plane, bool enable)
{
	int bit;

	if (plane == OMAP_DSS_GFX)
		bit = 14;
	else
		bit = 23;

	REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(plane), enable, bit, bit);
}
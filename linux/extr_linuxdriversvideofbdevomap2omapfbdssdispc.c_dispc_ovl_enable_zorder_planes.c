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

/* Variables and functions */
 int /*<<< orphan*/  DISPC_OVL_ATTRIBUTES (int) ; 
 int /*<<< orphan*/  FEAT_ALPHA_FREE_ZORDER ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int dss_feat_get_num_ovls () ; 
 int /*<<< orphan*/  dss_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dispc_ovl_enable_zorder_planes(void)
{
	int i;

	if (!dss_has_feature(FEAT_ALPHA_FREE_ZORDER))
		return;

	for (i = 0; i < dss_feat_get_num_ovls(); i++)
		REG_FLD_MOD(DISPC_OVL_ATTRIBUTES(i), 1, 25, 25);
}
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
 int /*<<< orphan*/  DISPC_CONTROL ; 
 int /*<<< orphan*/  FEAT_PCKFREEENABLE ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  dss_has_feature (int /*<<< orphan*/ ) ; 

void dispc_pck_free_enable(bool enable)
{
	if (!dss_has_feature(FEAT_PCKFREEENABLE))
		return;

	REG_FLD_MOD(DISPC_CONTROL, enable ? 1 : 0, 27, 27);
}
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
typedef  enum omap_dss_venc_type { ____Placeholder_omap_dss_venc_type } omap_dss_venc_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSS_CONTROL ; 
 int OMAP_DSS_VENC_TYPE_COMPOSITE ; 
 int OMAP_DSS_VENC_TYPE_SVIDEO ; 
 int /*<<< orphan*/  REG_FLD_MOD (int /*<<< orphan*/ ,int,int,int) ; 

void dss_set_venc_output(enum omap_dss_venc_type type)
{
	int l = 0;

	if (type == OMAP_DSS_VENC_TYPE_COMPOSITE)
		l = 0;
	else if (type == OMAP_DSS_VENC_TYPE_SVIDEO)
		l = 1;
	else
		BUG();

	/* venc out selection. 0 = comp, 1 = svideo */
	REG_FLD_MOD(DSS_CONTROL, l, 6, 6);
}
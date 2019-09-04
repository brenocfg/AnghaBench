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
struct dispc_features {int dummy; } ;

/* Variables and functions */
#define  OMAPDSS_VER_AM35xx 138 
#define  OMAPDSS_VER_AM43xx 137 
#define  OMAPDSS_VER_DRA7xx 136 
#define  OMAPDSS_VER_OMAP24xx 135 
#define  OMAPDSS_VER_OMAP34xx_ES1 134 
#define  OMAPDSS_VER_OMAP34xx_ES3 133 
#define  OMAPDSS_VER_OMAP3630 132 
#define  OMAPDSS_VER_OMAP4 131 
#define  OMAPDSS_VER_OMAP4430_ES1 130 
#define  OMAPDSS_VER_OMAP4430_ES2 129 
#define  OMAPDSS_VER_OMAP5 128 
 struct dispc_features const omap24xx_dispc_feats ; 
 struct dispc_features const omap34xx_rev1_0_dispc_feats ; 
 struct dispc_features const omap34xx_rev3_0_dispc_feats ; 
 struct dispc_features const omap44xx_dispc_feats ; 
 struct dispc_features const omap54xx_dispc_feats ; 
 int omapdss_get_version () ; 

__attribute__((used)) static const struct dispc_features *dispc_get_features(void)
{
	switch (omapdss_get_version()) {
	case OMAPDSS_VER_OMAP24xx:
		return &omap24xx_dispc_feats;

	case OMAPDSS_VER_OMAP34xx_ES1:
		return &omap34xx_rev1_0_dispc_feats;

	case OMAPDSS_VER_OMAP34xx_ES3:
	case OMAPDSS_VER_OMAP3630:
	case OMAPDSS_VER_AM35xx:
	case OMAPDSS_VER_AM43xx:
		return &omap34xx_rev3_0_dispc_feats;

	case OMAPDSS_VER_OMAP4430_ES1:
	case OMAPDSS_VER_OMAP4430_ES2:
	case OMAPDSS_VER_OMAP4:
		return &omap44xx_dispc_feats;

	case OMAPDSS_VER_OMAP5:
	case OMAPDSS_VER_DRA7xx:
		return &omap54xx_dispc_feats;

	default:
		return NULL;
	}
}
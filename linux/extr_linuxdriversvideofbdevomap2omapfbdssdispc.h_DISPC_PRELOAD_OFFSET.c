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
typedef  int u16 ;
typedef  enum omap_plane { ____Placeholder_omap_plane } omap_plane ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAP_DSS_GFX 131 
#define  OMAP_DSS_VIDEO1 130 
#define  OMAP_DSS_VIDEO2 129 
#define  OMAP_DSS_VIDEO3 128 

__attribute__((used)) static inline u16 DISPC_PRELOAD_OFFSET(enum omap_plane plane)
{
	switch (plane) {
	case OMAP_DSS_GFX:
		return 0x01AC;
	case OMAP_DSS_VIDEO1:
		return 0x0174;
	case OMAP_DSS_VIDEO2:
		return 0x00E8;
	case OMAP_DSS_VIDEO3:
		return 0x00A0;
	default:
		BUG();
		return 0;
	}
}
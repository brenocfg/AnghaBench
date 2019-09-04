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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  OMAP_DSS_CHANNEL_DIGIT 131 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 

__attribute__((used)) static inline u16 DISPC_DEFAULT_COLOR(enum omap_channel channel)
{
	switch (channel) {
	case OMAP_DSS_CHANNEL_LCD:
		return 0x004C;
	case OMAP_DSS_CHANNEL_DIGIT:
		return 0x0050;
	case OMAP_DSS_CHANNEL_LCD2:
		return 0x03AC;
	case OMAP_DSS_CHANNEL_LCD3:
		return 0x0814;
	default:
		BUG();
		return 0;
	}
}
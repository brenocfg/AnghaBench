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
struct ci_hdrc {TYPE_1__* platdata; } ;
struct TYPE_2__ {scalar_t__ phy_mode; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  OP_ULPI_VIEWPORT ; 
 int /*<<< orphan*/  ULPI_SYNC_STATE ; 
 scalar_t__ USBPHY_INTERFACE_MODE_ULPI ; 
 scalar_t__ hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

int ci_ulpi_resume(struct ci_hdrc *ci)
{
	int cnt = 100000;

	if (ci->platdata->phy_mode != USBPHY_INTERFACE_MODE_ULPI)
		return 0;

	while (cnt-- > 0) {
		if (hw_read(ci, OP_ULPI_VIEWPORT, ULPI_SYNC_STATE))
			return 0;
		udelay(1);
	}

	return -ETIMEDOUT;
}
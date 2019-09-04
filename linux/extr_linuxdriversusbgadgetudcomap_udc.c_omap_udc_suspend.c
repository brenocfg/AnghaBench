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
typedef  int u32 ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 int UDC_ATT ; 
 int /*<<< orphan*/  UDC_DEVSTAT ; 
 int UDC_SUS ; 
 int /*<<< orphan*/  WARNING (char*) ; 
 int /*<<< orphan*/  omap_pullup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int omap_readw (int /*<<< orphan*/ ) ; 
 TYPE_1__* udc ; 

__attribute__((used)) static int omap_udc_suspend(struct platform_device *dev, pm_message_t message)
{
	u32	devstat;

	devstat = omap_readw(UDC_DEVSTAT);

	/* we're requesting 48 MHz clock if the pullup is enabled
	 * (== we're attached to the host) and we're not suspended,
	 * which would prevent entry to deep sleep...
	 */
	if ((devstat & UDC_ATT) != 0 && (devstat & UDC_SUS) == 0) {
		WARNING("session active; suspend requires disconnect\n");
		omap_pullup(&udc->gadget, 0);
	}

	return 0;
}
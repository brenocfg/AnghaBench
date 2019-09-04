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
struct rtllib_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* data_hard_resume ) (int /*<<< orphan*/ ) ;scalar_t__ raw_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtllib_start_monitor_mode(struct rtllib_device *ieee)
{
	/* reset hardware status */
	if (ieee->raw_tx) {
		if (ieee->data_hard_resume)
			ieee->data_hard_resume(ieee->dev);

		netif_carrier_on(ieee->dev);
	}
}
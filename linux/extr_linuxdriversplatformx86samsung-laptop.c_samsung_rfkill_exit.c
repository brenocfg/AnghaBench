#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rfkill; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rfkill; } ;
struct samsung_laptop {TYPE_2__ bluetooth; TYPE_1__ wlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfkill_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void samsung_rfkill_exit(struct samsung_laptop *samsung)
{
	if (samsung->wlan.rfkill) {
		rfkill_unregister(samsung->wlan.rfkill);
		rfkill_destroy(samsung->wlan.rfkill);
		samsung->wlan.rfkill = NULL;
	}
	if (samsung->bluetooth.rfkill) {
		rfkill_unregister(samsung->bluetooth.rfkill);
		rfkill_destroy(samsung->bluetooth.rfkill);
		samsung->bluetooth.rfkill = NULL;
	}
}
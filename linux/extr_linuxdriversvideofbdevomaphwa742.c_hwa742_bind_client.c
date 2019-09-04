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
struct omapfb_notifier_block {int dummy; } ;
struct TYPE_4__ {scalar_t__ update_mode; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAPFB_EVENT_READY ; 
 scalar_t__ OMAPFB_MANUAL_UPDATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 TYPE_2__ hwa742 ; 
 int /*<<< orphan*/  omapfb_notify_clients (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hwa742_bind_client(struct omapfb_notifier_block *nb)
{
	dev_dbg(hwa742.fbdev->dev, "update_mode %d\n", hwa742.update_mode);
	if (hwa742.update_mode == OMAPFB_MANUAL_UPDATE) {
		omapfb_notify_clients(hwa742.fbdev, OMAPFB_EVENT_READY);
	}
}
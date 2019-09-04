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
struct lapb_cb {int /*<<< orphan*/  dev; TYPE_1__* callbacks; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* disconnect_confirmation ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

void lapb_disconnect_confirmation(struct lapb_cb *lapb, int reason)
{
	if (lapb->callbacks->disconnect_confirmation)
		lapb->callbacks->disconnect_confirmation(lapb->dev, reason);
}
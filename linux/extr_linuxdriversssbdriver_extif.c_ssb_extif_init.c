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
struct ssb_extif {int /*<<< orphan*/  gpio_lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void ssb_extif_init(struct ssb_extif *extif)
{
	if (!extif->dev)
		return; /* We don't have a Extif core */
	spin_lock_init(&extif->gpio_lock);
}
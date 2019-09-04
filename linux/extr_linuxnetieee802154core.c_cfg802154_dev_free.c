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
struct cfg802154_registered_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cfg802154_registered_device*) ; 

void cfg802154_dev_free(struct cfg802154_registered_device *rdev)
{
	kfree(rdev);
}
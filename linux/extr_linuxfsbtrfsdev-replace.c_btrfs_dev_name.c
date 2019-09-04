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
struct btrfs_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_DEV_STATE_MISSING ; 
 char* rcu_str_deref (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char* btrfs_dev_name(struct btrfs_device *device)
{
	if (!device || test_bit(BTRFS_DEV_STATE_MISSING, &device->dev_state))
		return "<missing disk>";
	else
		return rcu_str_deref(device->name);
}
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
struct btrfs_device {int /*<<< orphan*/  flush_bio; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_device*) ; 
 int /*<<< orphan*/  rcu_string_free (int /*<<< orphan*/ ) ; 

void btrfs_free_device(struct btrfs_device *device)
{
	rcu_string_free(device->name);
	bio_put(device->flush_bio);
	kfree(device);
}
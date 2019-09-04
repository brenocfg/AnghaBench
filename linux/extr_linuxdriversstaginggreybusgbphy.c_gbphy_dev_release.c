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
struct gbphy_device {int /*<<< orphan*/  id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gbphy_id ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gbphy_device*) ; 
 struct gbphy_device* to_gbphy_dev (struct device*) ; 

__attribute__((used)) static void gbphy_dev_release(struct device *dev)
{
	struct gbphy_device *gbphy_dev = to_gbphy_dev(dev);

	ida_simple_remove(&gbphy_id, gbphy_dev->id);
	kfree(gbphy_dev);
}
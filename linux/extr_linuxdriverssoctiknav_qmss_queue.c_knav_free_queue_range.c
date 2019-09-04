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
struct knav_range_info {int /*<<< orphan*/  list; TYPE_1__* ops; } ;
struct knav_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_range ) (struct knav_range_info*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct knav_range_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct knav_range_info*) ; 

__attribute__((used)) static void knav_free_queue_range(struct knav_device *kdev,
				  struct knav_range_info *range)
{
	if (range->ops && range->ops->free_range)
		range->ops->free_range(range);
	list_del(&range->list);
	devm_kfree(kdev->dev, range);
}
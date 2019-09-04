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
struct nvme_ns {TYPE_2__* ctrl; } ;
struct gendisk {struct nvme_ns* private_data; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_put_ns (struct nvme_ns*) ; 

__attribute__((used)) static void nvme_release(struct gendisk *disk, fmode_t mode)
{
	struct nvme_ns *ns = disk->private_data;

	module_put(ns->ctrl->ops->module);
	nvme_put_ns(ns);
}
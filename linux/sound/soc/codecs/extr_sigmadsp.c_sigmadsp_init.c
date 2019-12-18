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
struct sigmadsp_ops {int dummy; } ;
struct sigmadsp {int /*<<< orphan*/  lock; int /*<<< orphan*/  data_list; int /*<<< orphan*/  ctrl_list; struct device* dev; struct sigmadsp_ops const* ops; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sigmadsp_firmware_load (struct sigmadsp*,char const*) ; 

__attribute__((used)) static int sigmadsp_init(struct sigmadsp *sigmadsp, struct device *dev,
	const struct sigmadsp_ops *ops, const char *firmware_name)
{
	sigmadsp->ops = ops;
	sigmadsp->dev = dev;

	INIT_LIST_HEAD(&sigmadsp->ctrl_list);
	INIT_LIST_HEAD(&sigmadsp->data_list);
	mutex_init(&sigmadsp->lock);

	return sigmadsp_firmware_load(sigmadsp, firmware_name);
}
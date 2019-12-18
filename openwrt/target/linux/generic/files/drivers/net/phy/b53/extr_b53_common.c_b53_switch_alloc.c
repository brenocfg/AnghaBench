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
struct device {int dummy; } ;
struct b53_io_ops {int dummy; } ;
struct b53_device {int /*<<< orphan*/  reg_mutex; void* priv; struct b53_io_ops* ops; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct b53_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct b53_device *b53_switch_alloc(struct device *base, struct b53_io_ops *ops,
				    void *priv)
{
	struct b53_device *dev;

	dev = devm_kzalloc(base, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return NULL;

	dev->dev = base;
	dev->ops = ops;
	dev->priv = priv;
	mutex_init(&dev->reg_mutex);

	return dev;
}
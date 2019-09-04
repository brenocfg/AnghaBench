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
struct resource {int dummy; } ;
struct TYPE_2__ {struct device* parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct ci_hdrc_platform_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct platform_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ci_get_platdata (struct device*,struct ci_hdrc_platform_data*) ; 
 int /*<<< orphan*/  ci_ida ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct ci_hdrc_platform_data*,int) ; 
 int platform_device_add_resources (struct platform_device*,struct resource*,int) ; 
 struct platform_device* platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

struct platform_device *ci_hdrc_add_device(struct device *dev,
			struct resource *res, int nres,
			struct ci_hdrc_platform_data *platdata)
{
	struct platform_device *pdev;
	int id, ret;

	ret = ci_get_platdata(dev, platdata);
	if (ret)
		return ERR_PTR(ret);

	id = ida_simple_get(&ci_ida, 0, 0, GFP_KERNEL);
	if (id < 0)
		return ERR_PTR(id);

	pdev = platform_device_alloc("ci_hdrc", id);
	if (!pdev) {
		ret = -ENOMEM;
		goto put_id;
	}

	pdev->dev.parent = dev;

	ret = platform_device_add_resources(pdev, res, nres);
	if (ret)
		goto err;

	ret = platform_device_add_data(pdev, platdata, sizeof(*platdata));
	if (ret)
		goto err;

	ret = platform_device_add(pdev);
	if (ret)
		goto err;

	return pdev;

err:
	platform_device_put(pdev);
put_id:
	ida_simple_remove(&ci_ida, id);
	return ERR_PTR(ret);
}
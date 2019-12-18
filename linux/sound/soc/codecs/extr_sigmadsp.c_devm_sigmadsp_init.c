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
struct sigmadsp {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct sigmadsp* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_sigmadsp_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct sigmadsp*) ; 
 struct sigmadsp* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct sigmadsp*) ; 
 int sigmadsp_init (struct sigmadsp*,struct device*,struct sigmadsp_ops const*,char const*) ; 

struct sigmadsp *devm_sigmadsp_init(struct device *dev,
	const struct sigmadsp_ops *ops, const char *firmware_name)
{
	struct sigmadsp *sigmadsp;
	int ret;

	sigmadsp = devres_alloc(devm_sigmadsp_release, sizeof(*sigmadsp),
		GFP_KERNEL);
	if (!sigmadsp)
		return ERR_PTR(-ENOMEM);

	ret = sigmadsp_init(sigmadsp, dev, ops, firmware_name);
	if (ret) {
		devres_free(sigmadsp);
		return ERR_PTR(ret);
	}

	devres_add(dev, sigmadsp);

	return sigmadsp;
}
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
struct byt_pinctrl_soc_data {int ncommunities; struct byt_community* communities; } ;
struct byt_gpio {TYPE_1__* pdev; struct byt_pinctrl_soc_data const* soc_data; struct byt_community* communities_copy; } ;
struct byt_community {int /*<<< orphan*/  reg_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct byt_community* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int byt_set_soc_data(struct byt_gpio *vg,
			    const struct byt_pinctrl_soc_data *soc_data)
{
	int i;

	vg->soc_data = soc_data;
	vg->communities_copy = devm_kcalloc(&vg->pdev->dev,
					    soc_data->ncommunities,
					    sizeof(*vg->communities_copy),
					    GFP_KERNEL);
	if (!vg->communities_copy)
		return -ENOMEM;

	for (i = 0; i < soc_data->ncommunities; i++) {
		struct byt_community *comm = vg->communities_copy + i;
		struct resource *mem_rc;

		*comm = vg->soc_data->communities[i];

		mem_rc = platform_get_resource(vg->pdev, IORESOURCE_MEM, 0);
		comm->reg_base = devm_ioremap_resource(&vg->pdev->dev, mem_rc);
		if (IS_ERR(comm->reg_base))
			return PTR_ERR(comm->reg_base);
	}

	return 0;
}
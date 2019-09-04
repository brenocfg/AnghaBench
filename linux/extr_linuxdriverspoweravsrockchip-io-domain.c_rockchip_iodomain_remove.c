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
struct rockchip_iodomain_supply {int /*<<< orphan*/  nb; scalar_t__ reg; } ;
struct rockchip_iodomain {struct rockchip_iodomain_supply* supplies; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int MAX_SUPPLIES ; 
 struct rockchip_iodomain* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  regulator_unregister_notifier (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_iodomain_remove(struct platform_device *pdev)
{
	struct rockchip_iodomain *iod = platform_get_drvdata(pdev);
	int i;

	for (i = MAX_SUPPLIES - 1; i >= 0; i--) {
		struct rockchip_iodomain_supply *io_supply = &iod->supplies[i];

		if (io_supply->reg)
			regulator_unregister_notifier(io_supply->reg,
						      &io_supply->nb);
	}

	return 0;
}
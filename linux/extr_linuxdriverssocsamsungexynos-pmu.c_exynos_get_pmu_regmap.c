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
struct regmap {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_pmu_of_device_ids ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

struct regmap *exynos_get_pmu_regmap(void)
{
	struct device_node *np = of_find_matching_node(NULL,
						      exynos_pmu_of_device_ids);
	if (np)
		return syscon_node_to_regmap(np);
	return ERR_PTR(-ENODEV);
}
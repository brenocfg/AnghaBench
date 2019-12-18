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
struct mtk_base_afe_dai {void* num_dapm_routes; void* dapm_routes; void* num_dapm_widgets; void* dapm_widgets; void* num_dai_drivers; void* dai_drivers; int /*<<< orphan*/  list; } ;
struct mtk_base_afe {int /*<<< orphan*/  sub_dais; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mtk_base_afe_dai* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* mt6797_memif_dai_driver ; 
 void* mt6797_memif_routes ; 
 void* mt6797_memif_widgets ; 

__attribute__((used)) static int mt6797_dai_memif_register(struct mtk_base_afe *afe)
{
	struct mtk_base_afe_dai *dai;

	dai = devm_kzalloc(afe->dev, sizeof(*dai), GFP_KERNEL);
	if (!dai)
		return -ENOMEM;

	list_add(&dai->list, &afe->sub_dais);

	dai->dai_drivers = mt6797_memif_dai_driver;
	dai->num_dai_drivers = ARRAY_SIZE(mt6797_memif_dai_driver);

	dai->dapm_widgets = mt6797_memif_widgets;
	dai->num_dapm_widgets = ARRAY_SIZE(mt6797_memif_widgets);
	dai->dapm_routes = mt6797_memif_routes;
	dai->num_dapm_routes = ARRAY_SIZE(mt6797_memif_routes);
	return 0;
}
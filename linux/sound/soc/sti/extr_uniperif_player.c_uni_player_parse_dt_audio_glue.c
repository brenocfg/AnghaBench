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
struct uniperif {void* valid_sel; void* clk_sel; int /*<<< orphan*/  id; } ;
struct regmap {int dummy; } ;
struct reg_field {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 struct reg_field REG_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYS_CFG_AUDIO_GLUE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 void* regmap_field_alloc (struct regmap*,struct reg_field) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int uni_player_parse_dt_audio_glue(struct platform_device *pdev,
					  struct uniperif *player)
{
	struct device_node *node = pdev->dev.of_node;
	struct regmap *regmap;
	struct reg_field regfield[2] = {
		/* PCM_CLK_SEL */
		REG_FIELD(SYS_CFG_AUDIO_GLUE,
			  8 + player->id,
			  8 + player->id),
		/* PCMP_VALID_SEL */
		REG_FIELD(SYS_CFG_AUDIO_GLUE, 0, 1)
	};

	regmap = syscon_regmap_lookup_by_phandle(node, "st,syscfg");

	if (IS_ERR(regmap)) {
		dev_err(&pdev->dev, "sti-audio-clk-glue syscf not found\n");
		return PTR_ERR(regmap);
	}

	player->clk_sel = regmap_field_alloc(regmap, regfield[0]);
	player->valid_sel = regmap_field_alloc(regmap, regfield[1]);

	return 0;
}
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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct es8328_priv {int /*<<< orphan*/  supplies; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int es8328_suspend(struct snd_soc_component *component)
{
	struct es8328_priv *es8328;
	int ret;

	es8328 = snd_soc_component_get_drvdata(component);

	clk_disable_unprepare(es8328->clk);

	ret = regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			es8328->supplies);
	if (ret) {
		dev_err(component->dev, "unable to disable regulators\n");
		return ret;
	}
	return 0;
}
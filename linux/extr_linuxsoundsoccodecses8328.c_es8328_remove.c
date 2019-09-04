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
struct snd_soc_component {int dummy; } ;
struct es8328_priv {int /*<<< orphan*/  supplies; scalar_t__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void es8328_remove(struct snd_soc_component *component)
{
	struct es8328_priv *es8328;

	es8328 = snd_soc_component_get_drvdata(component);

	if (es8328->clk)
		clk_disable_unprepare(es8328->clk);

	regulator_bulk_disable(ARRAY_SIZE(es8328->supplies),
			       es8328->supplies);
}
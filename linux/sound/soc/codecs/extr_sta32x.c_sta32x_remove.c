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
struct sta32x_priv {scalar_t__ xti_clk; int /*<<< orphan*/  supplies; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sta32x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  sta32x_watchdog_stop (struct sta32x_priv*) ; 

__attribute__((used)) static void sta32x_remove(struct snd_soc_component *component)
{
	struct sta32x_priv *sta32x = snd_soc_component_get_drvdata(component);

	sta32x_watchdog_stop(sta32x);
	regulator_bulk_disable(ARRAY_SIZE(sta32x->supplies), sta32x->supplies);

	if (sta32x->xti_clk)
		clk_disable_unprepare(sta32x->xti_clk);
}
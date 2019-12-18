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
struct ak4642_priv {scalar_t__ mcko; } ;

/* Variables and functions */
 int /*<<< orphan*/  ak4642_set_mcko (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (scalar_t__) ; 
 struct ak4642_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4642_probe(struct snd_soc_component *component)
{
	struct ak4642_priv *priv = snd_soc_component_get_drvdata(component);

	if (priv->mcko)
		ak4642_set_mcko(component, clk_get_rate(priv->mcko));

	return 0;
}
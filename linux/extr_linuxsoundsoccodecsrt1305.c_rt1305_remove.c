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
struct rt1305_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt1305_reset (int /*<<< orphan*/ ) ; 
 struct rt1305_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void rt1305_remove(struct snd_soc_component *component)
{
	struct rt1305_priv *rt1305 = snd_soc_component_get_drvdata(component);

	rt1305_reset(rt1305->regmap);
}
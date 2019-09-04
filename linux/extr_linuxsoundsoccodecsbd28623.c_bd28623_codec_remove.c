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
struct bd28623_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd28623_power_off (struct bd28623_priv*) ; 
 struct bd28623_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void bd28623_codec_remove(struct snd_soc_component *component)
{
	struct bd28623_priv *bd = snd_soc_component_get_drvdata(component);

	bd28623_power_off(bd);
}
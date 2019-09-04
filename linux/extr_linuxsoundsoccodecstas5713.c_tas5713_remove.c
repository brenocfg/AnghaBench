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
struct tas5713_priv {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct tas5713_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void tas5713_remove(struct snd_soc_component *component)
{
	struct tas5713_priv *tas5713;

	tas5713 = snd_soc_component_get_drvdata(component);
}
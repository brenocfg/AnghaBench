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
struct ak4458_priv {int fs; } ;

/* Variables and functions */
 int ak4458_init (struct snd_soc_component*) ; 
 struct ak4458_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int ak4458_probe(struct snd_soc_component *component)
{
	struct ak4458_priv *ak4458 = snd_soc_component_get_drvdata(component);

	ak4458->fs = 48000;

	return ak4458_init(component);
}
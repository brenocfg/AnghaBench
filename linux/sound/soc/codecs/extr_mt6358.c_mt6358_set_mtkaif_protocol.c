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
struct mt6358_priv {int mtkaif_protocol; } ;

/* Variables and functions */
 struct mt6358_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

int mt6358_set_mtkaif_protocol(struct snd_soc_component *cmpnt,
			       int mtkaif_protocol)
{
	struct mt6358_priv *priv = snd_soc_component_get_drvdata(cmpnt);

	priv->mtkaif_protocol = mtkaif_protocol;
	return 0;
}
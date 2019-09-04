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
struct snd_soc_dai_driver {int dummy; } ;
struct rsnd_priv {struct snd_soc_dai_driver* daidrv; } ;

/* Variables and functions */
 int rsnd_rdai_nr (struct rsnd_priv*) ; 

__attribute__((used)) static struct snd_soc_dai_driver
*rsnd_daidrv_get(struct rsnd_priv *priv, int id)
{
	if ((id < 0) || (id >= rsnd_rdai_nr(priv)))
		return NULL;

	return priv->daidrv + id;
}
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
struct ssp_priv {int /*<<< orphan*/  ssp; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ssp_priv*) ; 
 int /*<<< orphan*/  pxa_ssp_free (int /*<<< orphan*/ ) ; 
 struct ssp_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int pxa_ssp_remove(struct snd_soc_dai *dai)
{
	struct ssp_priv *priv = snd_soc_dai_get_drvdata(dai);

	pxa_ssp_free(priv->ssp);
	kfree(priv);
	return 0;
}
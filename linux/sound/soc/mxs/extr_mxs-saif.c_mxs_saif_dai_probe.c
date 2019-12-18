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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct mxs_saif {int dummy; } ;

/* Variables and functions */
 struct mxs_saif* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct mxs_saif*) ; 

__attribute__((used)) static int mxs_saif_dai_probe(struct snd_soc_dai *dai)
{
	struct mxs_saif *saif = dev_get_drvdata(dai->dev);

	snd_soc_dai_set_drvdata(dai, saif);

	return 0;
}
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
struct sspa_priv {int dummy; } ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sspa_priv* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_set_drvdata (struct snd_soc_dai*,struct sspa_priv*) ; 

__attribute__((used)) static int mmp_sspa_probe(struct snd_soc_dai *dai)
{
	struct sspa_priv *priv = dev_get_drvdata(dai->dev);

	snd_soc_dai_set_drvdata(dai, priv);
	return 0;

}
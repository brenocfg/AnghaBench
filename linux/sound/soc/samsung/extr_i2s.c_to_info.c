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
struct snd_soc_dai {int id; } ;
struct samsung_i2s_priv {struct i2s_dai* dai; } ;
struct i2s_dai {int dummy; } ;

/* Variables and functions */
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static inline struct i2s_dai *to_info(struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);

	return &priv->dai[dai->id - 1];
}
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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct max9867_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX9867_PWRMAN ; 
 int /*<<< orphan*/  MAX9867_SHTDOWN_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max9867_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int max9867_prepare(struct snd_pcm_substream *substream,
			 struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct max9867_priv *max9867 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(max9867->regmap, MAX9867_PWRMAN,
		MAX9867_SHTDOWN_MASK, MAX9867_SHTDOWN_MASK);
	return 0;
}
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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;
struct fsl_esai {int /*<<< orphan*/  regmap; scalar_t__ synchronous; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAI_SAICR_SYNC ; 
 int /*<<< orphan*/  ESAI_xCCR_xDC (int) ; 
 int /*<<< orphan*/  ESAI_xCCR_xDC_MASK ; 
 int /*<<< orphan*/  REG_ESAI_RCCR ; 
 int /*<<< orphan*/  REG_ESAI_SAICR ; 
 int /*<<< orphan*/  REG_ESAI_TCCR ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fsl_esai* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_esai_startup(struct snd_pcm_substream *substream,
			    struct snd_soc_dai *dai)
{
	struct fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	if (!dai->active) {
		/* Set synchronous mode */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_SAICR,
				   ESAI_SAICR_SYNC, esai_priv->synchronous ?
				   ESAI_SAICR_SYNC : 0);

		/* Set a default slot number -- 2 */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR,
				   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(2));
		regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR,
				   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(2));
	}

	return 0;

}
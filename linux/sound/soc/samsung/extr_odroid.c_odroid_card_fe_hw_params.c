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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  card; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct odroid_priv {scalar_t__ be_sample_rate; int /*<<< orphan*/  lock; scalar_t__ be_active; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ params_rate (struct snd_pcm_hw_params*) ; 
 struct odroid_priv* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int odroid_card_fe_hw_params(struct snd_pcm_substream *substream,
				      struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct odroid_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->be_active && priv->be_sample_rate != params_rate(params))
		ret = -EINVAL;
	spin_unlock_irqrestore(&priv->lock, flags);

	return ret;
}
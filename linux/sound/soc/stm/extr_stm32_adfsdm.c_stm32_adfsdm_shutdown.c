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
struct stm32_adfsdm_priv {int iio_active; int /*<<< orphan*/  lock; int /*<<< orphan*/  iio_cb; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_channel_stop_all_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stm32_adfsdm_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static void stm32_adfsdm_shutdown(struct snd_pcm_substream *substream,
				  struct snd_soc_dai *dai)
{
	struct stm32_adfsdm_priv *priv = snd_soc_dai_get_drvdata(dai);

	mutex_lock(&priv->lock);
	if (priv->iio_active) {
		iio_channel_stop_all_cb(priv->iio_cb);
		priv->iio_active = false;
	}
	mutex_unlock(&priv->lock);
}
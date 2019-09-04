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
struct s3c24xx_uda134x {scalar_t__ clk_users; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * xtal; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s3c24xx_uda134x* snd_soc_card_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c24xx_uda134x_shutdown(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct s3c24xx_uda134x *priv = snd_soc_card_get_drvdata(rtd->card);

	mutex_lock(&priv->clk_lock);
	priv->clk_users -= 1;
	if (priv->clk_users == 0) {
		clk_put(priv->xtal);
		priv->xtal = NULL;
		clk_put(priv->pclk);
		priv->pclk = NULL;
	}
	mutex_unlock(&priv->clk_lock);
}
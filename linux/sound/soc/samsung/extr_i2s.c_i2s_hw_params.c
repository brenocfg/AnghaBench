#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct samsung_i2s_priv {int /*<<< orphan*/  rclk_srcrate; struct clk** clk_table; int /*<<< orphan*/  lock; scalar_t__ addr; } ;
struct TYPE_6__ {int addr_width; } ;
struct TYPE_5__ {int addr_width; } ;
struct i2s_dai {int /*<<< orphan*/  frmclk; TYPE_3__ dma_capture; TYPE_2__ dma_playback; TYPE_1__* pdev; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CLK_I2S_RCLK_SRC ; 
 int EINVAL ; 
 scalar_t__ I2SMOD ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int MOD_BLCP_16BIT ; 
 int MOD_BLCP_24BIT ; 
 int MOD_BLCP_8BIT ; 
 int MOD_BLCP_MASK ; 
 int MOD_BLCS_16BIT ; 
 int MOD_BLCS_24BIT ; 
 int MOD_BLCS_8BIT ; 
 int MOD_BLCS_MASK ; 
 int MOD_BLC_16BIT ; 
 int MOD_BLC_24BIT ; 
 int MOD_BLC_8BIT ; 
 int MOD_BLC_MASK ; 
 int MOD_DC1_EN ; 
 int MOD_DC2_EN ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ is_manager (struct i2s_dai*) ; 
 scalar_t__ is_secondary (struct i2s_dai*) ; 
 int params_channels (struct snd_pcm_hw_params*) ; 
 int params_format (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct samsung_i2s_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int i2s_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct samsung_i2s_priv *priv = snd_soc_dai_get_drvdata(dai);
	struct i2s_dai *i2s = to_info(dai);
	u32 mod, mask = 0, val = 0;
	struct clk *rclksrc;
	unsigned long flags;

	WARN_ON(!pm_runtime_active(dai->dev));

	if (!is_secondary(i2s))
		mask |= (MOD_DC2_EN | MOD_DC1_EN);

	switch (params_channels(params)) {
	case 6:
		val |= MOD_DC2_EN;
		/* Fall through */
	case 4:
		val |= MOD_DC1_EN;
		break;
	case 2:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			i2s->dma_playback.addr_width = 4;
		else
			i2s->dma_capture.addr_width = 4;
		break;
	case 1:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			i2s->dma_playback.addr_width = 2;
		else
			i2s->dma_capture.addr_width = 2;

		break;
	default:
		dev_err(&i2s->pdev->dev, "%d channels not supported\n",
				params_channels(params));
		return -EINVAL;
	}

	if (is_secondary(i2s))
		mask |= MOD_BLCS_MASK;
	else
		mask |= MOD_BLCP_MASK;

	if (is_manager(i2s))
		mask |= MOD_BLC_MASK;

	switch (params_width(params)) {
	case 8:
		if (is_secondary(i2s))
			val |= MOD_BLCS_8BIT;
		else
			val |= MOD_BLCP_8BIT;
		if (is_manager(i2s))
			val |= MOD_BLC_8BIT;
		break;
	case 16:
		if (is_secondary(i2s))
			val |= MOD_BLCS_16BIT;
		else
			val |= MOD_BLCP_16BIT;
		if (is_manager(i2s))
			val |= MOD_BLC_16BIT;
		break;
	case 24:
		if (is_secondary(i2s))
			val |= MOD_BLCS_24BIT;
		else
			val |= MOD_BLCP_24BIT;
		if (is_manager(i2s))
			val |= MOD_BLC_24BIT;
		break;
	default:
		dev_err(&i2s->pdev->dev, "Format(%d) not supported\n",
				params_format(params));
		return -EINVAL;
	}

	spin_lock_irqsave(&priv->lock, flags);
	mod = readl(priv->addr + I2SMOD);
	mod = (mod & ~mask) | val;
	writel(mod, priv->addr + I2SMOD);
	spin_unlock_irqrestore(&priv->lock, flags);

	snd_soc_dai_init_dma_data(dai, &i2s->dma_playback, &i2s->dma_capture);

	i2s->frmclk = params_rate(params);

	rclksrc = priv->clk_table[CLK_I2S_RCLK_SRC];
	if (rclksrc && !IS_ERR(rclksrc))
		priv->rclk_srcrate = clk_get_rate(rclksrc);

	return 0;
}
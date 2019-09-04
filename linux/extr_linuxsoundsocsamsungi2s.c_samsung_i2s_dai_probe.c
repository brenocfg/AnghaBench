#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct i2s_dai {int quirks; int /*<<< orphan*/  lock; scalar_t__ rclk_srcrate; scalar_t__ bfs; scalar_t__ rfs; TYPE_2__* sec_dai; scalar_t__ addr; int /*<<< orphan*/  dma_capture; int /*<<< orphan*/  dma_playback; } ;
struct TYPE_3__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {TYPE_1__ idma_playback; int /*<<< orphan*/  dma_playback; } ;

/* Variables and functions */
 int /*<<< orphan*/  CON_RSTCLR ; 
 int /*<<< orphan*/  FIC_RXFLUSH ; 
 int /*<<< orphan*/  FIC_TXFLUSH ; 
 scalar_t__ I2SCON ; 
 int QUIRK_NEED_RSTCLR ; 
 int QUIRK_SUPPORTS_IDMA ; 
 int /*<<< orphan*/  SAMSUNG_I2S_CDCLK ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 struct i2s_dai* get_other_dai (struct i2s_dai*) ; 
 int /*<<< orphan*/  i2s_fifo (struct i2s_dai*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_rxctrl (struct i2s_dai*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_set_sysclk (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_txctrl (struct i2s_dai*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idma_reg_addr_init (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_opened (struct i2s_dai*) ; 
 scalar_t__ is_secondary (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dai_init_dma_data (struct snd_soc_dai*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int samsung_i2s_dai_probe(struct snd_soc_dai *dai)
{
	struct i2s_dai *i2s = to_info(dai);
	struct i2s_dai *other = get_other_dai(i2s);
	unsigned long flags;

	pm_runtime_get_sync(dai->dev);

	if (is_secondary(i2s)) { /* If this is probe on the secondary DAI */
		snd_soc_dai_init_dma_data(dai, &other->sec_dai->dma_playback,
					   NULL);
	} else {
		snd_soc_dai_init_dma_data(dai, &i2s->dma_playback,
					   &i2s->dma_capture);

		if (i2s->quirks & QUIRK_NEED_RSTCLR)
			writel(CON_RSTCLR, i2s->addr + I2SCON);

		if (i2s->quirks & QUIRK_SUPPORTS_IDMA)
			idma_reg_addr_init(i2s->addr,
					i2s->sec_dai->idma_playback.addr);
	}

	/* Reset any constraint on RFS and BFS */
	i2s->rfs = 0;
	i2s->bfs = 0;
	i2s->rclk_srcrate = 0;

	spin_lock_irqsave(i2s->lock, flags);
	i2s_txctrl(i2s, 0);
	i2s_rxctrl(i2s, 0);
	i2s_fifo(i2s, FIC_TXFLUSH);
	i2s_fifo(other, FIC_TXFLUSH);
	i2s_fifo(i2s, FIC_RXFLUSH);
	spin_unlock_irqrestore(i2s->lock, flags);

	/* Gate CDCLK by default */
	if (!is_opened(other))
		i2s_set_sysclk(dai, SAMSUNG_I2S_CDCLK,
				0, SND_SOC_CLOCK_IN);
	pm_runtime_put(dai->dev);

	return 0;
}
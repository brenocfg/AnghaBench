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
struct stm32_i2s_data {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * substream; int /*<<< orphan*/  i2sclk; int /*<<< orphan*/  regmap; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 scalar_t__ I2S_CGFR_MCKOE ; 
 int /*<<< orphan*/  STM32_I2S_CGFR_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 struct stm32_i2s_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void stm32_i2s_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *cpu_dai)
{
	struct stm32_i2s_data *i2s = snd_soc_dai_get_drvdata(cpu_dai);
	unsigned long flags;

	regmap_update_bits(i2s->regmap, STM32_I2S_CGFR_REG,
			   I2S_CGFR_MCKOE, (unsigned int)~I2S_CGFR_MCKOE);

	clk_disable_unprepare(i2s->i2sclk);

	spin_lock_irqsave(&i2s->irq_lock, flags);
	i2s->substream = NULL;
	spin_unlock_irqrestore(&i2s->irq_lock, flags);
}
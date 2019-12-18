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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct hi6210_i2s {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HII2S_I2S_CFG ; 
 int /*<<< orphan*/  HII2S_I2S_CFG__S2_IF_RX_EN ; 
 struct hi6210_i2s* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6210_read_reg (struct hi6210_i2s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi6210_write_reg (struct hi6210_i2s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hi6210_i2s_rxctrl(struct snd_soc_dai *cpu_dai, int on)
{
	struct hi6210_i2s *i2s = dev_get_drvdata(cpu_dai->dev);
	u32 val;

	spin_lock(&i2s->lock);
	if (on) {
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val |= HII2S_I2S_CFG__S2_IF_RX_EN;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
	} else {
		val = hi6210_read_reg(i2s, HII2S_I2S_CFG);
		val &= ~HII2S_I2S_CFG__S2_IF_RX_EN;
		hi6210_write_reg(i2s, HII2S_I2S_CFG, val);
	}
	spin_unlock(&i2s->lock);
}
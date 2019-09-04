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
struct img_i2s_in {int active_channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMG_I2S_IN_CH_CTL ; 
 int /*<<< orphan*/  IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK ; 
 int /*<<< orphan*/  img_i2s_in_ch_readl (struct img_i2s_in*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  img_i2s_in_ch_writel (struct img_i2s_in*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void img_i2s_in_flush(struct img_i2s_in *i2s)
{
	int i;
	u32 reg;

	for (i = 0; i < i2s->active_channels; i++) {
		reg = img_i2s_in_ch_readl(i2s, i, IMG_I2S_IN_CH_CTL);
		reg |= IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
		reg &= ~IMG_I2S_IN_CH_CTL_FIFO_FLUSH_MASK;
		img_i2s_in_ch_writel(i2s, i, reg, IMG_I2S_IN_CH_CTL);
	}
}
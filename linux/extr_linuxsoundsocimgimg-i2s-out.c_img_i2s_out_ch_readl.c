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
typedef  int u32 ;
struct img_i2s_out {int channel_base; } ;

/* Variables and functions */
 int IMG_I2S_OUT_CH_STRIDE ; 
 int readl (int) ; 

__attribute__((used)) static inline u32 img_i2s_out_ch_readl(struct img_i2s_out *i2s, u32 chan,
					u32 reg)
{
	return readl(i2s->channel_base + (chan * IMG_I2S_OUT_CH_STRIDE) + reg);
}
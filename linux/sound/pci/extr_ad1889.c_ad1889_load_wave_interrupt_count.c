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
struct snd_ad1889 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_DMA_WAVIB ; 
 int /*<<< orphan*/  AD_DMA_WAVIC ; 
 int /*<<< orphan*/  ad1889_writel (struct snd_ad1889*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ad1889_load_wave_interrupt_count(struct snd_ad1889 *chip, u32 count)
{
	ad1889_writel(chip, AD_DMA_WAVIB, count);
	ad1889_writel(chip, AD_DMA_WAVIC, count);
}
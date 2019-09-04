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
struct pcm512x_priv {int dummy; } ;

/* Variables and functions */
 unsigned long pcm512x_dac_max (struct pcm512x_priv*,int) ; 

__attribute__((used)) static unsigned long pcm512x_ncp_target(struct pcm512x_priv *pcm512x,
					unsigned long dac_rate)
{
	/*
	 * If the DAC is not actually overclocked, use the good old
	 * NCP target rate...
	 */
	if (dac_rate <= 6144000)
		return 1536000;
	/*
	 * ...but if the DAC is in fact overclocked, bump the NCP target
	 * rate to get the recommended dividers even when overclocking.
	 */
	return pcm512x_dac_max(pcm512x, 1536000);
}
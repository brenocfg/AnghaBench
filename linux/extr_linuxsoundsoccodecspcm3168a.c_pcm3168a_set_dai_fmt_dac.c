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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int pcm3168a_set_dai_fmt (struct snd_soc_dai*,unsigned int,int) ; 

__attribute__((used)) static int pcm3168a_set_dai_fmt_dac(struct snd_soc_dai *dai,
			       unsigned int format)
{
	return pcm3168a_set_dai_fmt(dai, format, true);
}
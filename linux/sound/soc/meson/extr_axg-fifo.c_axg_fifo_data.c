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
struct snd_pcm_substream {int dummy; } ;
struct axg_fifo {int dummy; } ;

/* Variables and functions */
 struct snd_soc_dai* axg_fifo_dai (struct snd_pcm_substream*) ; 
 struct axg_fifo* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static struct axg_fifo *axg_fifo_data(struct snd_pcm_substream *ss)
{
	struct snd_soc_dai *dai = axg_fifo_dai(ss);

	return snd_soc_dai_get_drvdata(dai);
}
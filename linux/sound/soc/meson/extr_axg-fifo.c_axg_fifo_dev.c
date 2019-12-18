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
struct snd_soc_dai {struct device* dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct snd_soc_dai* axg_fifo_dai (struct snd_pcm_substream*) ; 

__attribute__((used)) static struct device *axg_fifo_dev(struct snd_pcm_substream *ss)
{
	struct snd_soc_dai *dai = axg_fifo_dai(ss);

	return dai->dev;
}
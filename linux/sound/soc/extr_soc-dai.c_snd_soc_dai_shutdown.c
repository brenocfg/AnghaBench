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
struct snd_soc_dai {TYPE_2__* driver; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* shutdown ) (struct snd_pcm_substream*,struct snd_soc_dai*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*,struct snd_soc_dai*) ; 

void snd_soc_dai_shutdown(struct snd_soc_dai *dai,
			 struct snd_pcm_substream *substream)
{
	if (dai->driver->ops->shutdown)
		dai->driver->ops->shutdown(substream, dai);
}
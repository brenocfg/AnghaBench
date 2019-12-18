#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ number; struct snd_pcm_substream* next; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV_SG ; 
 int /*<<< orphan*/  snd_pcm_lib_preallocate_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ,struct device*,int,int) ; 

__attribute__((used)) static int snd_echo_preallocate_pages(struct snd_pcm *pcm, struct device *dev)
{
	struct snd_pcm_substream *ss;
	int stream;

	for (stream = 0; stream < 2; stream++)
		for (ss = pcm->streams[stream].substream; ss; ss = ss->next)
			snd_pcm_lib_preallocate_pages(ss, SNDRV_DMA_TYPE_DEV_SG,
						      dev,
						      ss->number ? 0 : 128<<10,
						      256<<10);

	return 0;
}
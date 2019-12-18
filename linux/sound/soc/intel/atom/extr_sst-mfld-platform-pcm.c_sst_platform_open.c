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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; TYPE_1__* pcm; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  hw; } ;
struct TYPE_2__ {scalar_t__ internal; } ;

/* Variables and functions */
 int /*<<< orphan*/  sst_platform_pcm_hw ; 

__attribute__((used)) static int sst_platform_open(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime;

	if (substream->pcm->internal)
		return 0;

	runtime = substream->runtime;
	runtime->hw = sst_platform_pcm_hw;
	return 0;
}
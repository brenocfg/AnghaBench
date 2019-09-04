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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 

__attribute__((used)) static int snd_nm256_pcm_hw_params(struct snd_pcm_substream *substream,
				   struct snd_pcm_hw_params *hw_params)
{
	/* area and addr are already set and unchanged */
	substream->runtime->dma_bytes = params_buffer_bytes(hw_params);
	return 0;
}
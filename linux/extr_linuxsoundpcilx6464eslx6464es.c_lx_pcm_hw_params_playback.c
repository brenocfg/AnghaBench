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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int lx_pcm_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lx_pcm_hw_params_playback(struct snd_pcm_substream *substream,
				 struct snd_pcm_hw_params *hw_params)
{
	return lx_pcm_hw_params(substream, hw_params, 0);
}
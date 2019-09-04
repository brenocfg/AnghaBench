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
struct snd_pcm_substream {struct channel* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_2__ {scalar_t__ channels_max; scalar_t__ channels_min; } ;
struct channel {TYPE_1__ pcm_hardware; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 scalar_t__ params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int snd_pcm_lib_alloc_vmalloc_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcm_hw_params(struct snd_pcm_substream *substream,
			 struct snd_pcm_hw_params *hw_params)
{
	struct channel *channel = substream->private_data;

	if ((params_channels(hw_params) > channel->pcm_hardware.channels_max) ||
	    (params_channels(hw_params) < channel->pcm_hardware.channels_min)) {
		pr_err("Requested number of channels not supported.\n");
		return -EINVAL;
	}
	return snd_pcm_lib_alloc_vmalloc_buffer(substream,
						params_buffer_bytes(hw_params));
}
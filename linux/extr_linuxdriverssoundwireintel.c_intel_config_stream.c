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
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct sdw_intel {TYPE_2__* res; } ;
struct TYPE_4__ {int /*<<< orphan*/  arg; TYPE_1__* ops; } ;
struct TYPE_3__ {int (* config_stream ) (int /*<<< orphan*/ ,struct snd_pcm_substream*,struct snd_soc_dai*,struct snd_pcm_hw_params*,int) ;} ;

/* Variables and functions */
 int EIO ; 
 int stub1 (int /*<<< orphan*/ ,struct snd_pcm_substream*,struct snd_soc_dai*,struct snd_pcm_hw_params*,int) ; 

__attribute__((used)) static int intel_config_stream(struct sdw_intel *sdw,
			struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai,
			struct snd_pcm_hw_params *hw_params, int link_id)
{
	if (sdw->res->ops && sdw->res->ops->config_stream)
		return sdw->res->ops->config_stream(sdw->res->arg,
				substream, dai, hw_params, link_id);

	return -EIO;
}
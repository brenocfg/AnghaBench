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
struct snd_soc_dai {int active; int /*<<< orphan*/  name; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int send_ssp_cmd (struct snd_soc_dai*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sst_be_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	int ret = 0;

	if (dai->active == 1)
		ret = send_ssp_cmd(dai, dai->name, 1);
	return ret;
}
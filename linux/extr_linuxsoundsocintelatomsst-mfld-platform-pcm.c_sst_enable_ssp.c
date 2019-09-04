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
struct snd_soc_dai {int /*<<< orphan*/  active; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sst_fill_ssp_defaults (struct snd_soc_dai*) ; 
 int sst_handle_vb_timer (struct snd_soc_dai*,int) ; 

__attribute__((used)) static int sst_enable_ssp(struct snd_pcm_substream *substream,
			struct snd_soc_dai *dai)
{
	int ret = 0;

	if (!dai->active) {
		ret = sst_handle_vb_timer(dai, true);
		sst_fill_ssp_defaults(dai);
	}
	return ret;
}
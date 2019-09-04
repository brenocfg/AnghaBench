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
struct soc_tplg {int dummy; } ;
struct snd_soc_tplg_pcm {int dummy; } ;

/* Variables and functions */
 int soc_tplg_dai_create (struct soc_tplg*,struct snd_soc_tplg_pcm*) ; 
 int soc_tplg_fe_link_create (struct soc_tplg*,struct snd_soc_tplg_pcm*) ; 

__attribute__((used)) static int soc_tplg_pcm_create(struct soc_tplg *tplg,
	struct snd_soc_tplg_pcm *pcm)
{
	int ret;

	ret = soc_tplg_dai_create(tplg, pcm);
	if (ret < 0)
		return ret;

	return  soc_tplg_fe_link_create(tplg, pcm);
}
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
struct snd_soc_pcm_runtime {struct snd_soc_pcm_runtime* codec_dais; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_soc_pcm_runtime*) ; 
 int /*<<< orphan*/  snd_soc_rtdcom_del_all (struct snd_soc_pcm_runtime*) ; 

__attribute__((used)) static void soc_free_pcm_runtime(struct snd_soc_pcm_runtime *rtd)
{
	kfree(rtd->codec_dais);
	snd_soc_rtdcom_del_all(rtd);
	kfree(rtd);
}
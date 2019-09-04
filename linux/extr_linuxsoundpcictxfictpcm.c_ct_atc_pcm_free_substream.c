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
struct snd_pcm_runtime {struct ct_atc_pcm* private_data; } ;
struct ct_atc_pcm {int /*<<< orphan*/  timer; int /*<<< orphan*/  substream; } ;
struct ct_atc {int /*<<< orphan*/  (* pcm_release_resources ) (struct ct_atc*,struct ct_atc_pcm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ct_timer_instance_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ct_atc_pcm*) ; 
 struct ct_atc* snd_pcm_substream_chip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ct_atc*,struct ct_atc_pcm*) ; 

__attribute__((used)) static void ct_atc_pcm_free_substream(struct snd_pcm_runtime *runtime)
{
	struct ct_atc_pcm *apcm = runtime->private_data;
	struct ct_atc *atc = snd_pcm_substream_chip(apcm->substream);

	atc->pcm_release_resources(atc, apcm);
	ct_timer_instance_free(apcm->timer);
	kfree(apcm);
	runtime->private_data = NULL;
}
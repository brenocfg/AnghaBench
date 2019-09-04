#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_card {TYPE_1__* dai_link; struct glb_pool* drvdata; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_3__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct glb_pool {int /*<<< orphan*/  set_rate; int /*<<< orphan*/  set_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int snd_allo_piano_dsp_program (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_card* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 struct snd_soc_pcm_runtime* snd_soc_get_pcm_runtime (struct snd_soc_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_allo_piano_lowpass_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_card *card = snd_kcontrol_chip(kcontrol);
	struct snd_soc_pcm_runtime *rtd;
	struct glb_pool *glb_ptr = card->drvdata;

	rtd = snd_soc_get_pcm_runtime(card, card->dai_link[0].name);
	return(snd_allo_piano_dsp_program(rtd,
				glb_ptr->set_mode, glb_ptr->set_rate,
				ucontrol->value.integer.value[0]));
}
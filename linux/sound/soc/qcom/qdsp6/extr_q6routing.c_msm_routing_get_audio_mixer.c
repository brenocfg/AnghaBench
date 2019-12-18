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
struct soc_mixer_control {int shift; scalar_t__ reg; } ;
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct session_data {scalar_t__ port_id; } ;
struct msm_routing_data {struct session_data* sessions; } ;

/* Variables and functions */
 struct msm_routing_data* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct snd_soc_dapm_context* snd_soc_dapm_kcontrol_dapm (struct snd_kcontrol*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static int msm_routing_get_audio_mixer(struct snd_kcontrol *kcontrol,
				       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm =
	    snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct soc_mixer_control *mc =
	    (struct soc_mixer_control *)kcontrol->private_value;
	int session_id = mc->shift;
	struct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	struct msm_routing_data *priv = dev_get_drvdata(c->dev);
	struct session_data *session = &priv->sessions[session_id];

	if (session->port_id == mc->reg)
		ucontrol->value.integer.value[0] = 1;
	else
		ucontrol->value.integer.value[0] = 0;

	return 0;
}
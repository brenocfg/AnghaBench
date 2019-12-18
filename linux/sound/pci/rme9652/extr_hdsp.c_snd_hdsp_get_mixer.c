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
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdsp {int max_channels; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int hdsp_input_to_output_key (struct hdsp*,int,int) ; 
 int hdsp_playback_to_output_key (struct hdsp*,int,int) ; 
 int hdsp_read_gain (struct hdsp*,int) ; 
 struct hdsp* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdsp_get_mixer(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct hdsp *hdsp = snd_kcontrol_chip(kcontrol);
	int source;
	int destination;
	int addr;

	source = ucontrol->value.integer.value[0];
	destination = ucontrol->value.integer.value[1];

	if (source >= hdsp->max_channels)
		addr = hdsp_playback_to_output_key(hdsp,source-hdsp->max_channels,destination);
	else
		addr = hdsp_input_to_output_key(hdsp,source, destination);

	spin_lock_irq(&hdsp->lock);
	ucontrol->value.integer.value[2] = hdsp_read_gain (hdsp, addr);
	spin_unlock_irq(&hdsp->lock);
	return 0;
}
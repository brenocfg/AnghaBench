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
struct hdspm {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int HDSPM_MAX_CHANNELS ; 
 int hdspm_read_in_gain (struct hdspm*,int,int) ; 
 int hdspm_read_pb_gain (struct hdspm*,int,int) ; 
 int /*<<< orphan*/  hdspm_write_in_gain (struct hdspm*,int,int,int) ; 
 int /*<<< orphan*/  hdspm_write_pb_gain (struct hdspm*,int,int,int) ; 
 int /*<<< orphan*/  snd_hdspm_use_is_exclusive (struct hdspm*) ; 
 struct hdspm* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_hdspm_put_mixer(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	int change;
	int source;
	int destination;
	int gain;

	if (!snd_hdspm_use_is_exclusive(hdspm))
		return -EBUSY;

	source = ucontrol->value.integer.value[0];
	destination = ucontrol->value.integer.value[1];

	if (source < 0 || source >= 2 * HDSPM_MAX_CHANNELS)
		return -1;
	if (destination < 0 || destination >= HDSPM_MAX_CHANNELS)
		return -1;

	gain = ucontrol->value.integer.value[2];

	spin_lock_irq(&hdspm->lock);

	if (source >= HDSPM_MAX_CHANNELS)
		change = gain != hdspm_read_pb_gain(hdspm, destination,
						    source -
						    HDSPM_MAX_CHANNELS);
	else
		change = gain != hdspm_read_in_gain(hdspm, destination,
						    source);

	if (change) {
		if (source >= HDSPM_MAX_CHANNELS)
			hdspm_write_pb_gain(hdspm, destination,
					    source - HDSPM_MAX_CHANNELS,
					    gain);
		else
			hdspm_write_in_gain(hdspm, destination, source,
					    gain);
	}
	spin_unlock_irq(&hdspm->lock);

	return change;
}
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
struct snd_kcontrol {struct oxygen* private_data; } ;
struct snd_ctl_elem_value {int dummy; } ;
struct oxygen {int /*<<< orphan*/  mutex; int /*<<< orphan*/  spdif_pcm_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxygen_to_iec958 (int /*<<< orphan*/ ,struct snd_ctl_elem_value*) ; 

__attribute__((used)) static int spdif_pcm_get(struct snd_kcontrol *ctl,
			 struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;

	mutex_lock(&chip->mutex);
	oxygen_to_iec958(chip->spdif_pcm_bits, value);
	mutex_unlock(&chip->mutex);
	return 0;
}
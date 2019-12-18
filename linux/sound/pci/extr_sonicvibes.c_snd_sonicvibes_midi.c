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
struct sonicvibes {struct snd_card* card; } ;
struct snd_rawmidi {struct snd_mpu401* private_data; } ;
struct snd_mpu401 {int /*<<< orphan*/  close_input; int /*<<< orphan*/  open_input; struct sonicvibes* private_data; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct sonicvibes*) ; 
 int /*<<< orphan*/ * snd_sonicvibes_midi_controls ; 
 int /*<<< orphan*/  snd_sonicvibes_midi_input_close ; 
 int /*<<< orphan*/  snd_sonicvibes_midi_input_open ; 

__attribute__((used)) static int snd_sonicvibes_midi(struct sonicvibes *sonic,
			       struct snd_rawmidi *rmidi)
{
	struct snd_mpu401 * mpu = rmidi->private_data;
	struct snd_card *card = sonic->card;
	unsigned int idx;
	int err;

	mpu->private_data = sonic;
	mpu->open_input = snd_sonicvibes_midi_input_open;
	mpu->close_input = snd_sonicvibes_midi_input_close;
	for (idx = 0; idx < ARRAY_SIZE(snd_sonicvibes_midi_controls); idx++)
		if ((err = snd_ctl_add(card, snd_ctl_new1(&snd_sonicvibes_midi_controls[idx], sonic))) < 0)
			return err;
	return 0;
}
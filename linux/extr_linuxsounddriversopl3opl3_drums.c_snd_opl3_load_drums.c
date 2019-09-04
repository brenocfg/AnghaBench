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
struct snd_opl3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bass_note ; 
 int /*<<< orphan*/  bass_op0 ; 
 int /*<<< orphan*/  bass_op1 ; 
 int /*<<< orphan*/  cymbal ; 
 int /*<<< orphan*/  hihat ; 
 int /*<<< orphan*/  snare ; 
 int /*<<< orphan*/  snare_note ; 
 int /*<<< orphan*/  snd_opl3_drum_note_set (struct snd_opl3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_opl3_drum_voice_set (struct snd_opl3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tomtom ; 
 int /*<<< orphan*/  tomtom_note ; 

void snd_opl3_load_drums(struct snd_opl3 *opl3)
{
	snd_opl3_drum_voice_set(opl3, &bass_op0);
	snd_opl3_drum_voice_set(opl3, &bass_op1);
	snd_opl3_drum_note_set(opl3, &bass_note);

	snd_opl3_drum_voice_set(opl3, &hihat);

	snd_opl3_drum_voice_set(opl3, &snare);
	snd_opl3_drum_note_set(opl3, &snare_note);

	snd_opl3_drum_voice_set(opl3, &tomtom);
	snd_opl3_drum_note_set(opl3, &tomtom_note);

	snd_opl3_drum_voice_set(opl3, &cymbal);
}
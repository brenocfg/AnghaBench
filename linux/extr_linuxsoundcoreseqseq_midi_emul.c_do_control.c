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
struct snd_midi_op {int /*<<< orphan*/  (* control ) (void*,int,struct snd_midi_channel*) ;int /*<<< orphan*/  (* note_off ) (void*,int,int /*<<< orphan*/ ,struct snd_midi_channel*) ;} ;
struct snd_midi_channel_set {int /*<<< orphan*/  midi_mode; } ;
struct snd_midi_channel {int* control; int* note; int drum_channel; int /*<<< orphan*/  param_type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
#define  MIDI_CTL_ALL_NOTES_OFF 154 
#define  MIDI_CTL_ALL_SOUNDS_OFF 153 
#define  MIDI_CTL_E1_REVERB_DEPTH 152 
#define  MIDI_CTL_E2_TREMOLO_DEPTH 151 
#define  MIDI_CTL_E3_CHORUS_DEPTH 150 
#define  MIDI_CTL_E4_DETUNE_DEPTH 149 
#define  MIDI_CTL_E5_PHASER_DEPTH 148 
#define  MIDI_CTL_HOLD2 147 
#define  MIDI_CTL_LEGATO_FOOTSWITCH 146 
#define  MIDI_CTL_LSB_BANK 145 
#define  MIDI_CTL_LSB_DATA_ENTRY 144 
#define  MIDI_CTL_MSB_BANK 143 
#define  MIDI_CTL_MSB_DATA_ENTRY 142 
#define  MIDI_CTL_NONREG_PARM_NUM_LSB 141 
#define  MIDI_CTL_NONREG_PARM_NUM_MSB 140 
#define  MIDI_CTL_PORTAMENTO 139 
#define  MIDI_CTL_REGIST_PARM_NUM_LSB 138 
#define  MIDI_CTL_REGIST_PARM_NUM_MSB 137 
#define  MIDI_CTL_RESET_CONTROLLERS 136 
#define  MIDI_CTL_SC1_SOUND_VARIATION 135 
#define  MIDI_CTL_SC2_TIMBRE 134 
#define  MIDI_CTL_SC3_RELEASE_TIME 133 
#define  MIDI_CTL_SC4_ATTACK_TIME 132 
#define  MIDI_CTL_SC5_BRIGHTNESS 131 
#define  MIDI_CTL_SOFT_PEDAL 130 
#define  MIDI_CTL_SOSTENUTO 129 
#define  MIDI_CTL_SUSTAIN 128 
 int /*<<< orphan*/  SNDRV_MIDI_MODE_XG ; 
 void* SNDRV_MIDI_NOTE_OFF ; 
 int SNDRV_MIDI_NOTE_ON ; 
 int SNDRV_MIDI_NOTE_RELEASED ; 
 int SNDRV_MIDI_NOTE_SOSTENUTO ; 
 int /*<<< orphan*/  SNDRV_MIDI_PARAM_TYPE_NONREGISTERED ; 
 int /*<<< orphan*/  SNDRV_MIDI_PARAM_TYPE_REGISTERED ; 
 int /*<<< orphan*/  all_notes_off (struct snd_midi_op*,void*,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  all_sounds_off (struct snd_midi_op*,void*,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  nrpn (struct snd_midi_op*,void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ; 
 int /*<<< orphan*/  rpn (struct snd_midi_op*,void*,struct snd_midi_channel*,struct snd_midi_channel_set*) ; 
 int /*<<< orphan*/  snd_midi_reset_controllers (struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub1 (void*,int,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub2 (void*,int,int /*<<< orphan*/ ,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  stub3 (void*,int,struct snd_midi_channel*) ; 

__attribute__((used)) static void
do_control(struct snd_midi_op *ops, void *drv, struct snd_midi_channel_set *chset,
	   struct snd_midi_channel *chan, int control, int value)
{
	int  i;

	if (control >= ARRAY_SIZE(chan->control))
		return;

	/* Switches */
	if ((control >=64 && control <=69) || (control >= 80 && control <= 83)) {
		/* These are all switches; either off or on so set to 0 or 127 */
		value = (value >= 64)? 127: 0;
	}
	chan->control[control] = value;

	switch (control) {
	case MIDI_CTL_SUSTAIN:
		if (value == 0) {
			/* Sustain has been released, turn off held notes */
			for (i = 0; i < 128; i++) {
				if (chan->note[i] & SNDRV_MIDI_NOTE_RELEASED) {
					chan->note[i] = SNDRV_MIDI_NOTE_OFF;
					if (ops->note_off)
						ops->note_off(drv, i, 0, chan);
				}
			}
		}
		break;
	case MIDI_CTL_PORTAMENTO:
		break;
	case MIDI_CTL_SOSTENUTO:
		if (value) {
			/* Mark each note that is currently held down */
			for (i = 0; i < 128; i++) {
				if (chan->note[i] & SNDRV_MIDI_NOTE_ON)
					chan->note[i] |= SNDRV_MIDI_NOTE_SOSTENUTO;
			}
		} else {
			/* release all notes that were held */
			for (i = 0; i < 128; i++) {
				if (chan->note[i] & SNDRV_MIDI_NOTE_SOSTENUTO) {
					chan->note[i] &= ~SNDRV_MIDI_NOTE_SOSTENUTO;
					if (chan->note[i] & SNDRV_MIDI_NOTE_RELEASED) {
						chan->note[i] = SNDRV_MIDI_NOTE_OFF;
						if (ops->note_off)
							ops->note_off(drv, i, 0, chan);
					}
				}
			}
		}
		break;
	case MIDI_CTL_MSB_DATA_ENTRY:
		chan->control[MIDI_CTL_LSB_DATA_ENTRY] = 0;
		/* fall through */
	case MIDI_CTL_LSB_DATA_ENTRY:
		if (chan->param_type == SNDRV_MIDI_PARAM_TYPE_REGISTERED)
			rpn(ops, drv, chan, chset);
		else
			nrpn(ops, drv, chan, chset);
		break;
	case MIDI_CTL_REGIST_PARM_NUM_LSB:
	case MIDI_CTL_REGIST_PARM_NUM_MSB:
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_REGISTERED;
		break;
	case MIDI_CTL_NONREG_PARM_NUM_LSB:
	case MIDI_CTL_NONREG_PARM_NUM_MSB:
		chan->param_type = SNDRV_MIDI_PARAM_TYPE_NONREGISTERED;
		break;

	case MIDI_CTL_ALL_SOUNDS_OFF:
		all_sounds_off(ops, drv, chan);
		break;

	case MIDI_CTL_ALL_NOTES_OFF:
		all_notes_off(ops, drv, chan);
		break;

	case MIDI_CTL_MSB_BANK:
		if (chset->midi_mode == SNDRV_MIDI_MODE_XG) {
			if (value == 127)
				chan->drum_channel = 1;
			else
				chan->drum_channel = 0;
		}
		break;
	case MIDI_CTL_LSB_BANK:
		break;

	case MIDI_CTL_RESET_CONTROLLERS:
		snd_midi_reset_controllers(chan);
		break;

	case MIDI_CTL_SOFT_PEDAL:
	case MIDI_CTL_LEGATO_FOOTSWITCH:
	case MIDI_CTL_HOLD2:
	case MIDI_CTL_SC1_SOUND_VARIATION:
	case MIDI_CTL_SC2_TIMBRE:
	case MIDI_CTL_SC3_RELEASE_TIME:
	case MIDI_CTL_SC4_ATTACK_TIME:
	case MIDI_CTL_SC5_BRIGHTNESS:
	case MIDI_CTL_E1_REVERB_DEPTH:
	case MIDI_CTL_E2_TREMOLO_DEPTH:
	case MIDI_CTL_E3_CHORUS_DEPTH:
	case MIDI_CTL_E4_DETUNE_DEPTH:
	case MIDI_CTL_E5_PHASER_DEPTH:
		goto notyet;
	notyet:
	default:
		if (ops->control)
			ops->control(drv, control, chan);
		break;
	}
}
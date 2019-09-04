#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_opl3_voice {scalar_t__ state; unsigned char keyon_reg; int note_off_check; int note; scalar_t__ time; struct snd_midi_channel* chan; scalar_t__ note_off; } ;
struct snd_opl3 {scalar_t__ synth_mode; unsigned short connection_reg; int /*<<< orphan*/  voice_lock; int /*<<< orphan*/  use_time; struct snd_opl3_voice* voices; int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,unsigned char) ;int /*<<< orphan*/  hardware; } ;
struct snd_midi_channel {unsigned char gm_bank_select; unsigned char midi_program; size_t number; int gm_pan; scalar_t__ drum_channel; } ;
struct fm_instrument {int* feedback_connection; int fix_key; int trnsps; int fix_dur; int modes; TYPE_1__* op; } ;
struct fm_patch {int type; struct fm_instrument inst; } ;
struct TYPE_2__ {unsigned char ksl_level; unsigned char am_vib; unsigned char attack_decay; unsigned char sustain_release; unsigned char wave_select; } ;

/* Variables and functions */
#define  FM_PATCH_OPL2 129 
#define  FM_PATCH_OPL3 128 
 int HZ ; 
 int MAX_OPL2_VOICES ; 
 size_t MAX_OPL3_VOICES ; 
 unsigned char OPL3_CONNECTION_BIT ; 
 int /*<<< orphan*/  OPL3_HW_OPL3 ; 
 unsigned char OPL3_KEYON_BIT ; 
 unsigned short OPL3_LEFT ; 
 unsigned char OPL3_LEFT_4OP_0 ; 
 unsigned char OPL3_REG_AM_VIB ; 
 unsigned char OPL3_REG_ATTACK_DECAY ; 
 unsigned short OPL3_REG_CONNECTION_SELECT ; 
 unsigned char OPL3_REG_FEEDBACK_CONNECTION ; 
 unsigned char OPL3_REG_FNUM_LOW ; 
 unsigned char OPL3_REG_KEYON_BLOCK ; 
 unsigned char OPL3_REG_KSL_LEVEL ; 
 unsigned char OPL3_REG_SUSTAIN_RELEASE ; 
 unsigned char OPL3_REG_WAVE_SELECT ; 
 unsigned short OPL3_RIGHT ; 
 unsigned char OPL3_RIGHT_4OP_0 ; 
 unsigned char OPL3_STEREO_BITS ; 
 unsigned char OPL3_VOICE_TO_LEFT ; 
 unsigned char OPL3_VOICE_TO_RIGHT ; 
 scalar_t__ SNDRV_OPL3_MODE_SEQ ; 
 scalar_t__ SNDRV_OPL3_ST_NOT_AVAIL ; 
 scalar_t__ SNDRV_OPL3_ST_OFF ; 
 scalar_t__ SNDRV_OPL3_ST_ON_2OP ; 
 scalar_t__ SNDRV_OPL3_ST_ON_4OP ; 
 scalar_t__ jiffies ; 
 int opl3_get_voice (struct snd_opl3*,int,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  snd_opl3_calc_pitch (unsigned char*,unsigned char*,int,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  snd_opl3_calc_volume (unsigned char*,int,struct snd_midi_channel*) ; 
 int /*<<< orphan*/  snd_opl3_drum_switch (struct snd_opl3*,int,int,int,struct snd_midi_channel*) ; 
 struct fm_patch* snd_opl3_find_patch (struct snd_opl3*,unsigned char,unsigned char,int /*<<< orphan*/ ) ; 
 int* snd_opl3_oss_map ; 
 unsigned char** snd_opl3_regmap ; 
 int /*<<< orphan*/  snd_opl3_start_timer (struct snd_opl3*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub10 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub11 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub12 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub13 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub3 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub4 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub5 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub6 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub7 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub8 (struct snd_opl3*,unsigned short,unsigned char) ; 
 int /*<<< orphan*/  stub9 (struct snd_opl3*,unsigned short,unsigned char) ; 
 scalar_t__ use_internal_drums ; 

void snd_opl3_note_on(void *p, int note, int vel, struct snd_midi_channel *chan)
{
	struct snd_opl3 *opl3;
	int instr_4op;

	int voice;
	struct snd_opl3_voice *vp, *vp2;
	unsigned short connect_mask;
	unsigned char connection;
	unsigned char vol_op[4];

	int extra_prg = 0;

	unsigned short reg_side;
	unsigned char op_offset;
	unsigned char voice_offset;
	unsigned short opl3_reg;
	unsigned char reg_val;
	unsigned char prg, bank;

	int key = note;
	unsigned char fnum, blocknum;
	int i;

	struct fm_patch *patch;
	struct fm_instrument *fm;
	unsigned long flags;

	opl3 = p;

#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "Note on, ch %i, inst %i, note %i, vel %i\n",
		   chan->number, chan->midi_program, note, vel);
#endif

	/* in SYNTH mode, application takes care of voices */
	/* in SEQ mode, drum voice numbers are notes on drum channel */
	if (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) {
		if (chan->drum_channel) {
			/* percussion instruments are located in bank 128 */
			bank = 128;
			prg = note;
		} else {
			bank = chan->gm_bank_select;
			prg = chan->midi_program;
		}
	} else {
		/* Prepare for OSS mode */
		if (chan->number >= MAX_OPL3_VOICES)
			return;

		/* OSS instruments are located in bank 127 */
		bank = 127;
		prg = chan->midi_program;
	}

	spin_lock_irqsave(&opl3->voice_lock, flags);

	if (use_internal_drums) {
		snd_opl3_drum_switch(opl3, note, vel, 1, chan);
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		return;
	}

 __extra_prg:
	patch = snd_opl3_find_patch(opl3, prg, bank, 0);
	if (!patch) {
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		return;
	}

	fm = &patch->inst;
	switch (patch->type) {
	case FM_PATCH_OPL2:
		instr_4op = 0;
		break;
	case FM_PATCH_OPL3:
		if (opl3->hardware >= OPL3_HW_OPL3) {
			instr_4op = 1;
			break;
		}
		/* fall through */
	default:
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		return;
	}
#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "  --> OPL%i instrument: %s\n",
		   instr_4op ? 3 : 2, patch->name);
#endif
	/* in SYNTH mode, application takes care of voices */
	/* in SEQ mode, allocate voice on free OPL3 channel */
	if (opl3->synth_mode == SNDRV_OPL3_MODE_SEQ) {
		voice = opl3_get_voice(opl3, instr_4op, chan);
	} else {
		/* remap OSS voice */
		voice = snd_opl3_oss_map[chan->number];		
	}

	if (voice < 0) {
		spin_unlock_irqrestore(&opl3->voice_lock, flags);
		return;
	}

	if (voice < MAX_OPL2_VOICES) {
		/* Left register block for voices 0 .. 8 */
		reg_side = OPL3_LEFT;
		voice_offset = voice;
		connect_mask = (OPL3_LEFT_4OP_0 << voice_offset) & 0x07;
	} else {
		/* Right register block for voices 9 .. 17 */
		reg_side = OPL3_RIGHT;
		voice_offset = voice - MAX_OPL2_VOICES;
		connect_mask = (OPL3_RIGHT_4OP_0 << voice_offset) & 0x38;
	}

	/* kill voice on channel */
	vp = &opl3->voices[voice];
	if (vp->state > 0) {
		opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
		reg_val = vp->keyon_reg & ~OPL3_KEYON_BIT;
		opl3->command(opl3, opl3_reg, reg_val);
	}
	if (instr_4op) {
		vp2 = &opl3->voices[voice + 3];
		if (vp->state > 0) {
			opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK +
					       voice_offset + 3);
			reg_val = vp->keyon_reg & ~OPL3_KEYON_BIT;
			opl3->command(opl3, opl3_reg, reg_val);
		}
	}

	/* set connection register */
	if (instr_4op) {
		if ((opl3->connection_reg ^ connect_mask) & connect_mask) {
			opl3->connection_reg |= connect_mask;
			/* set connection bit */
			opl3_reg = OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT;
			opl3->command(opl3, opl3_reg, opl3->connection_reg);
		}
	} else {
		if ((opl3->connection_reg ^ ~connect_mask) & connect_mask) {
			opl3->connection_reg &= ~connect_mask;
			/* clear connection bit */
			opl3_reg = OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT;
			opl3->command(opl3, opl3_reg, opl3->connection_reg);
		}
	}

#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "  --> setting OPL3 connection: 0x%x\n",
		   opl3->connection_reg);
#endif
	/*
	 * calculate volume depending on connection
	 * between FM operators (see include/opl3.h)
	 */
	for (i = 0; i < (instr_4op ? 4 : 2); i++)
		vol_op[i] = fm->op[i].ksl_level;

	connection = fm->feedback_connection[0] & 0x01;
	if (instr_4op) {
		connection <<= 1;
		connection |= fm->feedback_connection[1] & 0x01;

		snd_opl3_calc_volume(&vol_op[3], vel, chan);
		switch (connection) {
		case 0x03:
			snd_opl3_calc_volume(&vol_op[2], vel, chan);
			/* fallthru */
		case 0x02:
			snd_opl3_calc_volume(&vol_op[0], vel, chan);
			break;
		case 0x01:
			snd_opl3_calc_volume(&vol_op[1], vel, chan);
		}
	} else {
		snd_opl3_calc_volume(&vol_op[1], vel, chan);
		if (connection)
			snd_opl3_calc_volume(&vol_op[0], vel, chan);
	}

	/* Program the FM voice characteristics */
	for (i = 0; i < (instr_4op ? 4 : 2); i++) {
#ifdef DEBUG_MIDI
		snd_printk(KERN_DEBUG "  --> programming operator %i\n", i);
#endif
		op_offset = snd_opl3_regmap[voice_offset][i];

		/* Set OPL3 AM_VIB register of requested voice/operator */ 
		reg_val = fm->op[i].am_vib;
		opl3_reg = reg_side | (OPL3_REG_AM_VIB + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 KSL_LEVEL register of requested voice/operator */ 
		reg_val = vol_op[i];
		opl3_reg = reg_side | (OPL3_REG_KSL_LEVEL + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 ATTACK_DECAY register of requested voice/operator */ 
		reg_val = fm->op[i].attack_decay;
		opl3_reg = reg_side | (OPL3_REG_ATTACK_DECAY + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Set OPL3 SUSTAIN_RELEASE register of requested voice/operator */ 
		reg_val = fm->op[i].sustain_release;
		opl3_reg = reg_side | (OPL3_REG_SUSTAIN_RELEASE + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);

		/* Select waveform */
		reg_val = fm->op[i].wave_select;
		opl3_reg = reg_side | (OPL3_REG_WAVE_SELECT + op_offset);
		opl3->command(opl3, opl3_reg, reg_val);
	}

	/* Set operator feedback and 2op inter-operator connection */
	reg_val = fm->feedback_connection[0];
	/* Set output voice connection */
	reg_val |= OPL3_STEREO_BITS;
	if (chan->gm_pan < 43)
		reg_val &= ~OPL3_VOICE_TO_RIGHT;
	if (chan->gm_pan > 85)
		reg_val &= ~OPL3_VOICE_TO_LEFT;
	opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION + voice_offset);
	opl3->command(opl3, opl3_reg, reg_val);

	if (instr_4op) {
		/* Set 4op inter-operator connection */
		reg_val = fm->feedback_connection[1] & OPL3_CONNECTION_BIT;
		/* Set output voice connection */
		reg_val |= OPL3_STEREO_BITS;
		if (chan->gm_pan < 43)
			reg_val &= ~OPL3_VOICE_TO_RIGHT;
		if (chan->gm_pan > 85)
			reg_val &= ~OPL3_VOICE_TO_LEFT;
		opl3_reg = reg_side | (OPL3_REG_FEEDBACK_CONNECTION +
				       voice_offset + 3);
		opl3->command(opl3, opl3_reg, reg_val);
	}

	/*
	 * Special treatment of percussion notes for fm:
	 * Requested pitch is really program, and pitch for
	 * device is whatever was specified in the patch library.
	 */
	if (fm->fix_key)
		note = fm->fix_key;
	/*
	 * use transpose if defined in patch library
	 */
	if (fm->trnsps)
		note += (fm->trnsps - 64);

	snd_opl3_calc_pitch(&fnum, &blocknum, note, chan);

	/* Set OPL3 FNUM_LOW register of requested voice */
	opl3_reg = reg_side | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, fnum);

	opl3->voices[voice].keyon_reg = blocknum;

	/* Set output sound flag */
	blocknum |= OPL3_KEYON_BIT;

#ifdef DEBUG_MIDI
	snd_printk(KERN_DEBUG "  --> trigger voice %i\n", voice);
#endif
	/* Set OPL3 KEYON_BLOCK register of requested voice */ 
	opl3_reg = reg_side | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, blocknum);

	/* kill note after fixed duration (in centiseconds) */
	if (fm->fix_dur) {
		opl3->voices[voice].note_off = jiffies +
			(fm->fix_dur * HZ) / 100;
		snd_opl3_start_timer(opl3);
		opl3->voices[voice].note_off_check = 1;
	} else
		opl3->voices[voice].note_off_check = 0;

	/* get extra pgm, but avoid possible loops */
	extra_prg = (extra_prg) ? 0 : fm->modes;

	/* do the bookkeeping */
	vp->time = opl3->use_time++;
	vp->note = key;
	vp->chan = chan;

	if (instr_4op) {
		vp->state = SNDRV_OPL3_ST_ON_4OP;

		vp2 = &opl3->voices[voice + 3];
		vp2->time = opl3->use_time++;
		vp2->note = key;
		vp2->chan = chan;
		vp2->state = SNDRV_OPL3_ST_NOT_AVAIL;
	} else {
		if (vp->state == SNDRV_OPL3_ST_ON_4OP) {
			/* 4op killed by 2op, release bounded voice */
			vp2 = &opl3->voices[voice + 3];
			vp2->time = opl3->use_time++;
			vp2->state = SNDRV_OPL3_ST_OFF;
		}
		vp->state = SNDRV_OPL3_ST_ON_2OP;
	}

#ifdef DEBUG_ALLOC
	debug_alloc(opl3, "note on ", voice);
#endif

	/* allocate extra program if specified in patch library */
	if (extra_prg) {
		if (extra_prg > 128) {
			bank = 128;
			/* percussions start at 35 */
			prg = extra_prg - 128 + 35 - 1;
		} else {
			bank = 0;
			prg = extra_prg - 1;
		}
#ifdef DEBUG_MIDI
		snd_printk(KERN_DEBUG " *** allocating extra program\n");
#endif
		goto __extra_prg;
	}
	spin_unlock_irqrestore(&opl3->voice_lock, flags);
}
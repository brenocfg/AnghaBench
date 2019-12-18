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
struct snd_opl3_drum_note {unsigned char voice; int /*<<< orphan*/  octave_f; int /*<<< orphan*/  fnum; } ;
struct snd_opl3 {int /*<<< orphan*/  (* command ) (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned char OPL3_LEFT ; 
 unsigned char OPL3_REG_FNUM_LOW ; 
 unsigned char OPL3_REG_KEYON_BLOCK ; 
 int /*<<< orphan*/  stub1 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_opl3*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_opl3_drum_note_set(struct snd_opl3 *opl3,
				   struct snd_opl3_drum_note *data)
{
	unsigned char voice_offset = data->voice;
	unsigned short opl3_reg;

	/* Set OPL3 FNUM_LOW register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_FNUM_LOW + voice_offset);
	opl3->command(opl3, opl3_reg, data->fnum);

	/* Set OPL3 KEYON_BLOCK register */ 
	opl3_reg = OPL3_LEFT | (OPL3_REG_KEYON_BLOCK + voice_offset);
	opl3->command(opl3, opl3_reg, data->octave_f);
}
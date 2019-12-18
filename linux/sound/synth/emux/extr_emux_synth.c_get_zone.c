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
struct snd_sf_zone {int dummy; } ;
struct snd_midi_channel {int midi_program; } ;
struct snd_emux_port {int* ctrls; } ;
struct snd_emux {int /*<<< orphan*/  sflist; } ;

/* Variables and functions */
 size_t EMUX_MD_DEF_BANK ; 
 size_t EMUX_MD_DEF_DRUM ; 
 scalar_t__ SF_IS_DRUM_BANK (int) ; 
 int /*<<< orphan*/  SNDRV_EMUX_MAX_MULTI_VOICES ; 
 int get_bank (struct snd_emux_port*,struct snd_midi_channel*) ; 
 int snd_soundfont_search_zone (int /*<<< orphan*/ ,int*,int,int,int,int,int,struct snd_sf_zone**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_zone(struct snd_emux *emu, struct snd_emux_port *port,
	 int *notep, int vel, struct snd_midi_channel *chan,
	 struct snd_sf_zone **table)
{
	int preset, bank, def_preset, def_bank;

	bank = get_bank(port, chan);
	preset = chan->midi_program;

	if (SF_IS_DRUM_BANK(bank)) {
		def_preset = port->ctrls[EMUX_MD_DEF_DRUM];
		def_bank = bank;
	} else {
		def_preset = preset;
		def_bank = port->ctrls[EMUX_MD_DEF_BANK];
	}

	return snd_soundfont_search_zone(emu->sflist, notep, vel, preset, bank,
					 def_preset, def_bank,
					 table, SNDRV_EMUX_MAX_MULTI_VOICES);
}
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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; } ;
struct snd_emu10k1_voice {unsigned int number; TYPE_1__* epcm; } ;
struct snd_emu10k1_pcm_mixer {int* attn; } ;
struct snd_emu10k1 {int dummy; } ;
struct TYPE_2__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVCF ; 
 int /*<<< orphan*/  DCYSUSV ; 
 int /*<<< orphan*/  IFATN ; 
 int /*<<< orphan*/  VTFT ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  snd_emu10k1_voice_clear_loop_stop (struct snd_emu10k1*,unsigned int) ; 

__attribute__((used)) static void snd_emu10k1_playback_prepare_voice(struct snd_emu10k1 *emu, struct snd_emu10k1_voice *evoice,
					       int master, int extra,
					       struct snd_emu10k1_pcm_mixer *mix)
{
	struct snd_pcm_substream *substream;
	struct snd_pcm_runtime *runtime;
	unsigned int attn, vattn;
	unsigned int voice, tmp;

	if (evoice == NULL)	/* skip second voice for mono */
		return;
	substream = evoice->epcm->substream;
	runtime = substream->runtime;
	voice = evoice->number;

	attn = extra ? 0 : 0x00ff;
	tmp = runtime->channels == 2 ? (master ? 1 : 2) : 0;
	vattn = mix != NULL ? (mix->attn[tmp] << 16) : 0;
	snd_emu10k1_ptr_write(emu, IFATN, voice, attn);
	snd_emu10k1_ptr_write(emu, VTFT, voice, vattn | 0xffff);
	snd_emu10k1_ptr_write(emu, CVCF, voice, vattn | 0xffff);
	snd_emu10k1_ptr_write(emu, DCYSUSV, voice, 0x7f7f);
	snd_emu10k1_voice_clear_loop_stop(emu, voice);
}
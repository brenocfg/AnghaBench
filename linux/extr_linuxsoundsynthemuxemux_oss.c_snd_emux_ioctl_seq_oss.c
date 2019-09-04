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
struct snd_seq_oss_arg {struct snd_emux_port* private_data; } ;
struct snd_emux_port {struct snd_emux* emu; } ;
struct snd_emux {int /*<<< orphan*/  memhdr; int /*<<< orphan*/  sflist; } ;

/* Variables and functions */
 int ENXIO ; 
#define  SNDCTL_SEQ_RESETSAMPLES 129 
#define  SNDCTL_SYNTH_MEMAVL 128 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_soundfont_remove_samples (int /*<<< orphan*/ ) ; 
 int snd_util_mem_avail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snd_emux_ioctl_seq_oss(struct snd_seq_oss_arg *arg, unsigned int cmd, unsigned long ioarg)
{
	struct snd_emux_port *p;
	struct snd_emux *emu;

	if (snd_BUG_ON(!arg))
		return -ENXIO;
	p = arg->private_data;
	if (snd_BUG_ON(!p))
		return -ENXIO;

	emu = p->emu;
	if (snd_BUG_ON(!emu))
		return -ENXIO;

	switch (cmd) {
	case SNDCTL_SEQ_RESETSAMPLES:
		snd_soundfont_remove_samples(emu->sflist);
		return 0;
			
	case SNDCTL_SYNTH_MEMAVL:
		if (emu->memhdr)
			return snd_util_mem_avail(emu->memhdr);
		return 0;
	}

	return 0;
}
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
struct snd_info_buffer {int dummy; } ;
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOLA_AMP_MUTE_CAPABLE (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_NUM_STEPS (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_OFFSET (unsigned int) ; 
 int /*<<< orphan*/  LOLA_AMP_STEP_SIZE (unsigned int) ; 
 unsigned int LOLA_PAR_AUDIO_WIDGET_CAP ; 
 int /*<<< orphan*/  LOLA_VERB_GET_MAX_LEVEL ; 
 int /*<<< orphan*/  lola_codec_read (struct lola*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lola_read_param (struct lola*,int,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int,...) ; 

__attribute__((used)) static void print_pin_widget(struct snd_info_buffer *buffer,
			     struct lola *chip, int nid, unsigned int ampcap,
			     const char *name)
{
	unsigned int val;

	lola_read_param(chip, nid, LOLA_PAR_AUDIO_WIDGET_CAP, &val);
	snd_iprintf(buffer, "Node 0x%02x %s wcaps 0x%x\n", nid, name, val);
	if (val == 0x00400200)
		return;
	lola_read_param(chip, nid, ampcap, &val);
	snd_iprintf(buffer, "  Amp-Caps: 0x%x\n", val);
	snd_iprintf(buffer, "    mute=%d, step-size=%d, steps=%d, ofs=%d\n",
		    LOLA_AMP_MUTE_CAPABLE(val),
		    LOLA_AMP_STEP_SIZE(val),
		    LOLA_AMP_NUM_STEPS(val),
		    LOLA_AMP_OFFSET(val));
	lola_codec_read(chip, nid, LOLA_VERB_GET_MAX_LEVEL, 0, 0, &val, NULL);
	snd_iprintf(buffer, "  Max-level: 0x%x\n", val);
}
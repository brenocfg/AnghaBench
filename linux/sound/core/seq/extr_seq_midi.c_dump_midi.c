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
struct snd_rawmidi_substream {struct snd_rawmidi_runtime* runtime; } ;
struct snd_rawmidi_runtime {int avail; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ printk_ratelimit () ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int snd_rawmidi_kernel_write (struct snd_rawmidi_substream*,char const*,int) ; 

__attribute__((used)) static int dump_midi(struct snd_rawmidi_substream *substream, const char *buf, int count)
{
	struct snd_rawmidi_runtime *runtime;
	int tmp;

	if (snd_BUG_ON(!substream || !buf))
		return -EINVAL;
	runtime = substream->runtime;
	if ((tmp = runtime->avail) < count) {
		if (printk_ratelimit())
			pr_err("ALSA: seq_midi: MIDI output buffer overrun\n");
		return -ENOMEM;
	}
	if (snd_rawmidi_kernel_write(substream, buf, count) < count)
		return -EINVAL;
	return 0;
}
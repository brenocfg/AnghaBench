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
struct snd_rawmidi_substream {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_input_trigger (struct snd_rawmidi_substream*,int) ; 
 long snd_rawmidi_kernel_read1 (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,unsigned char*,long) ; 

long snd_rawmidi_kernel_read(struct snd_rawmidi_substream *substream,
			     unsigned char *buf, long count)
{
	snd_rawmidi_input_trigger(substream, 1);
	return snd_rawmidi_kernel_read1(substream, NULL/*userbuf*/, buf, count);
}
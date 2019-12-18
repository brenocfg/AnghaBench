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
 long snd_rawmidi_kernel_write1 (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,unsigned char const*,long) ; 

long snd_rawmidi_kernel_write(struct snd_rawmidi_substream *substream,
			      const unsigned char *buf, long count)
{
	return snd_rawmidi_kernel_write1(substream, NULL, buf, count);
}
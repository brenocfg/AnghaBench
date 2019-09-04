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
typedef  void* u8 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_DATA ; 
 int /*<<< orphan*/  MPU_RXFIFO ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_INPUT ; 
 struct snd_rawmidi_substream* get_rawmidi_substream (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 void* inb (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  snd_rawmidi_receive (struct snd_rawmidi_substream*,void**,int) ; 

__attribute__((used)) static void vt1724_midi_read(struct snd_ice1712 *ice)
{
	struct snd_rawmidi_substream *s;
	int count, i;
	u8 buffer[32];

	s = get_rawmidi_substream(ice, SNDRV_RAWMIDI_STREAM_INPUT);
	count = inb(ICEREG1724(ice, MPU_RXFIFO));
	if (count > 0) {
		count = min(count, 32);
		for (i = 0; i < count; ++i)
			buffer[i] = inb(ICEREG1724(ice, MPU_DATA));
		snd_rawmidi_receive(s, buffer, count);
	}
}
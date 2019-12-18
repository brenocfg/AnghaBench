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
typedef  int /*<<< orphan*/  u8 ;
struct snd_rawmidi_substream {int dummy; } ;
struct snd_ice1712 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICEREG1724 (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPU_DATA ; 
 int /*<<< orphan*/  MPU_TXFIFO ; 
 int /*<<< orphan*/  SNDRV_RAWMIDI_STREAM_OUTPUT ; 
 int /*<<< orphan*/  VT1724_IRQ_MPU_TX ; 
 int /*<<< orphan*/  enable_midi_irq (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 struct snd_rawmidi_substream* get_rawmidi_substream (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_rawmidi_transmit (struct snd_rawmidi_substream*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_rawmidi_transmit_empty (struct snd_rawmidi_substream*) ; 

__attribute__((used)) static void vt1724_midi_write(struct snd_ice1712 *ice)
{
	struct snd_rawmidi_substream *s;
	int count, i;
	u8 buffer[32];

	s = get_rawmidi_substream(ice, SNDRV_RAWMIDI_STREAM_OUTPUT);
	count = 31 - inb(ICEREG1724(ice, MPU_TXFIFO));
	if (count > 0) {
		count = snd_rawmidi_transmit(s, buffer, count);
		for (i = 0; i < count; ++i)
			outb(buffer[i], ICEREG1724(ice, MPU_DATA));
	}
	/* mask irq when all bytes have been transmitted.
	 * enabled again in output_trigger when the new data comes in.
	 */
	enable_midi_irq(ice, VT1724_IRQ_MPU_TX,
			!snd_rawmidi_transmit_empty(s));
}
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
typedef  int u32 ;
typedef  int u16 ;
struct snd_pcm_substream {int dummy; } ;
struct snd_ice1712 {struct snd_pcm_substream* playback_con_substream; struct snd_pcm_substream* capture_con_substream; struct snd_pcm_substream** playback_con_substream_ds; struct snd_pcm_substream* capture_pro_substream; struct snd_pcm_substream* playback_pro_substream; TYPE_1__** rmidi; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  private_data; } ;

/* Variables and functions */
 unsigned char ICE1712_IRQ_CONCAP ; 
 unsigned char ICE1712_IRQ_CONPBK ; 
 unsigned char ICE1712_IRQ_FM ; 
 unsigned char ICE1712_IRQ_MPU1 ; 
 unsigned char ICE1712_IRQ_MPU2 ; 
 unsigned char ICE1712_IRQ_PBKDS ; 
 unsigned char ICE1712_IRQ_PROPCM ; 
 unsigned char ICE1712_IRQ_TIMER ; 
 unsigned char ICE1712_MULTI_CAPSTATUS ; 
 unsigned char ICE1712_MULTI_PBKSTATUS ; 
 int /*<<< orphan*/  ICEDS (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEMT (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICEREG (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTSTAT ; 
 int /*<<< orphan*/  IRQ ; 
 int /*<<< orphan*/  IRQSTAT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mpu401_uart_interrupt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static irqreturn_t snd_ice1712_interrupt(int irq, void *dev_id)
{
	struct snd_ice1712 *ice = dev_id;
	unsigned char status;
	int handled = 0;

	while (1) {
		status = inb(ICEREG(ice, IRQSTAT));
		if (status == 0)
			break;
		handled = 1;
		if (status & ICE1712_IRQ_MPU1) {
			if (ice->rmidi[0])
				snd_mpu401_uart_interrupt(irq, ice->rmidi[0]->private_data);
			outb(ICE1712_IRQ_MPU1, ICEREG(ice, IRQSTAT));
			status &= ~ICE1712_IRQ_MPU1;
		}
		if (status & ICE1712_IRQ_TIMER)
			outb(ICE1712_IRQ_TIMER, ICEREG(ice, IRQSTAT));
		if (status & ICE1712_IRQ_MPU2) {
			if (ice->rmidi[1])
				snd_mpu401_uart_interrupt(irq, ice->rmidi[1]->private_data);
			outb(ICE1712_IRQ_MPU2, ICEREG(ice, IRQSTAT));
			status &= ~ICE1712_IRQ_MPU2;
		}
		if (status & ICE1712_IRQ_PROPCM) {
			unsigned char mtstat = inb(ICEMT(ice, IRQ));
			if (mtstat & ICE1712_MULTI_PBKSTATUS) {
				if (ice->playback_pro_substream)
					snd_pcm_period_elapsed(ice->playback_pro_substream);
				outb(ICE1712_MULTI_PBKSTATUS, ICEMT(ice, IRQ));
			}
			if (mtstat & ICE1712_MULTI_CAPSTATUS) {
				if (ice->capture_pro_substream)
					snd_pcm_period_elapsed(ice->capture_pro_substream);
				outb(ICE1712_MULTI_CAPSTATUS, ICEMT(ice, IRQ));
			}
		}
		if (status & ICE1712_IRQ_FM)
			outb(ICE1712_IRQ_FM, ICEREG(ice, IRQSTAT));
		if (status & ICE1712_IRQ_PBKDS) {
			u32 idx;
			u16 pbkstatus;
			struct snd_pcm_substream *substream;
			pbkstatus = inw(ICEDS(ice, INTSTAT));
			/* dev_dbg(ice->card->dev, "pbkstatus = 0x%x\n", pbkstatus); */
			for (idx = 0; idx < 6; idx++) {
				if ((pbkstatus & (3 << (idx * 2))) == 0)
					continue;
				substream = ice->playback_con_substream_ds[idx];
				if (substream != NULL)
					snd_pcm_period_elapsed(substream);
				outw(3 << (idx * 2), ICEDS(ice, INTSTAT));
			}
			outb(ICE1712_IRQ_PBKDS, ICEREG(ice, IRQSTAT));
		}
		if (status & ICE1712_IRQ_CONCAP) {
			if (ice->capture_con_substream)
				snd_pcm_period_elapsed(ice->capture_con_substream);
			outb(ICE1712_IRQ_CONCAP, ICEREG(ice, IRQSTAT));
		}
		if (status & ICE1712_IRQ_CONPBK) {
			if (ice->playback_con_substream)
				snd_pcm_period_elapsed(ice->playback_con_substream);
			outb(ICE1712_IRQ_CONPBK, ICEREG(ice, IRQSTAT));
		}
	}
	return IRQ_RETVAL(handled);
}
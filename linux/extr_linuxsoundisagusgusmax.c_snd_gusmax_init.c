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
struct TYPE_2__ {int port; int dma1; int dma2; } ;
struct snd_gus_card {int equal_irq; int codec_flag; int max_cntrl_val; TYPE_1__ gf1; int /*<<< orphan*/  joystick_dac; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUSP (struct snd_gus_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXCNTRLPORT ; 
 int /*<<< orphan*/ * joystick_dac ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_gusmax_init(int dev, struct snd_card *card,
			    struct snd_gus_card *gus)
{
	gus->equal_irq = 1;
	gus->codec_flag = 1;
	gus->joystick_dac = joystick_dac[dev];
	/* init control register */
	gus->max_cntrl_val = (gus->gf1.port >> 4) & 0x0f;
	if (gus->gf1.dma1 > 3)
		gus->max_cntrl_val |= 0x10;
	if (gus->gf1.dma2 > 3)
		gus->max_cntrl_val |= 0x20;
	gus->max_cntrl_val |= 0x40;
	outb(gus->max_cntrl_val, GUSP(gus, MAXCNTRLPORT));
}
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
struct hdac_stream {int index; int running; int /*<<< orphan*/  substream; scalar_t__ period_wallclk; int /*<<< orphan*/  start_wallclk; struct hdac_bus* bus; } ;
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTCTL ; 
 int /*<<< orphan*/  SD_CTL ; 
 int /*<<< orphan*/  SD_CTL_3B ; 
 int SD_CTL_DMA_START ; 
 int /*<<< orphan*/  SD_CTL_STRIPE_MASK ; 
 int SD_INT_MASK ; 
 int /*<<< orphan*/  WALLCLK ; 
 int /*<<< orphan*/  snd_hdac_chip_readl (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_chip_updatel (struct hdac_bus*,int /*<<< orphan*/ ,int,int) ; 
 int snd_hdac_get_stream_stripe_ctl (struct hdac_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_updateb (struct hdac_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_snd_hdac_stream_start (struct hdac_bus*,struct hdac_stream*) ; 

void snd_hdac_stream_start(struct hdac_stream *azx_dev, bool fresh_start)
{
	struct hdac_bus *bus = azx_dev->bus;
	int stripe_ctl;

	trace_snd_hdac_stream_start(bus, azx_dev);

	azx_dev->start_wallclk = snd_hdac_chip_readl(bus, WALLCLK);
	if (!fresh_start)
		azx_dev->start_wallclk -= azx_dev->period_wallclk;

	/* enable SIE */
	snd_hdac_chip_updatel(bus, INTCTL,
			      1 << azx_dev->index,
			      1 << azx_dev->index);
	/* set stripe control */
	if (azx_dev->substream)
		stripe_ctl = snd_hdac_get_stream_stripe_ctl(bus, azx_dev->substream);
	else
		stripe_ctl = 0;
	snd_hdac_stream_updateb(azx_dev, SD_CTL_3B, SD_CTL_STRIPE_MASK,
				stripe_ctl);
	/* set DMA start and interrupt mask */
	snd_hdac_stream_updateb(azx_dev, SD_CTL,
				0, SD_CTL_DMA_START | SD_INT_MASK);
	azx_dev->running = true;
}
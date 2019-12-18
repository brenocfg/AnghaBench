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
struct hdac_stream {int running; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CTL ; 
 int /*<<< orphan*/  SD_CTL_3B ; 
 int SD_CTL_DMA_START ; 
 int SD_CTL_STRIPE_MASK ; 
 int SD_INT_MASK ; 
 int /*<<< orphan*/  SD_STS ; 
 int /*<<< orphan*/  snd_hdac_stream_updateb (struct hdac_stream*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_stream_writeb (struct hdac_stream*,int /*<<< orphan*/ ,int) ; 

void snd_hdac_stream_clear(struct hdac_stream *azx_dev)
{
	snd_hdac_stream_updateb(azx_dev, SD_CTL,
				SD_CTL_DMA_START | SD_INT_MASK, 0);
	snd_hdac_stream_writeb(azx_dev, SD_STS, SD_INT_MASK); /* to be sure */
	snd_hdac_stream_updateb(azx_dev, SD_CTL_3B, SD_CTL_STRIPE_MASK, 0);
	azx_dev->running = false;
}
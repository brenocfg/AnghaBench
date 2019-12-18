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
struct hdac_stream {scalar_t__ format_val; scalar_t__ period_bytes; scalar_t__ bufsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BDLPL ; 
 int /*<<< orphan*/  SD_BDLPU ; 
 int /*<<< orphan*/  SD_CTL ; 
 int /*<<< orphan*/  snd_hdac_stream_writel (struct hdac_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_hdac_stream_cleanup(struct hdac_stream *azx_dev)
{
	snd_hdac_stream_writel(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_writel(azx_dev, SD_BDLPU, 0);
	snd_hdac_stream_writel(azx_dev, SD_CTL, 0);
	azx_dev->bufsize = 0;
	azx_dev->period_bytes = 0;
	azx_dev->format_val = 0;
}
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
struct hdac_ext_stream {scalar_t__ pplc_addr; } ;

/* Variables and functions */
 unsigned char AZX_PPLCCTL_STRST ; 
 scalar_t__ AZX_REG_PPLCCTL ; 
 unsigned char readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_hdac_ext_link_stream_clear (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  snd_hdac_updatel (scalar_t__,scalar_t__,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

void snd_hdac_ext_link_stream_reset(struct hdac_ext_stream *stream)
{
	unsigned char val;
	int timeout;

	snd_hdac_ext_link_stream_clear(stream);

	snd_hdac_updatel(stream->pplc_addr, AZX_REG_PPLCCTL,
			 AZX_PPLCCTL_STRST, AZX_PPLCCTL_STRST);
	udelay(3);
	timeout = 50;
	do {
		val = readl(stream->pplc_addr + AZX_REG_PPLCCTL) &
				AZX_PPLCCTL_STRST;
		if (val)
			break;
		udelay(3);
	} while (--timeout);
	val &= ~AZX_PPLCCTL_STRST;
	writel(val, stream->pplc_addr + AZX_REG_PPLCCTL);
	udelay(3);

	timeout = 50;
	/* waiting for hardware to report that the stream is out of reset */
	do {
		val = readl(stream->pplc_addr + AZX_REG_PPLCCTL) & AZX_PPLCCTL_STRST;
		if (!val)
			break;
		udelay(3);
	} while (--timeout);

}
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
struct hdac_stream {unsigned int stream_tag; } ;
struct hdac_ext_stream {scalar_t__ pplc_addr; struct hdac_stream hstream; } ;

/* Variables and functions */
 unsigned int AZX_PPLCCTL_STRM_MASK ; 
 unsigned int AZX_PPLCCTL_STRM_SHIFT ; 
 scalar_t__ AZX_REG_PPLCCTL ; 
 scalar_t__ AZX_REG_PPLCFMT ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  snd_hdac_ext_link_stream_clear (struct hdac_ext_stream*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

int snd_hdac_ext_link_stream_setup(struct hdac_ext_stream *stream, int fmt)
{
	struct hdac_stream *hstream = &stream->hstream;
	unsigned int val;

	/* make sure the run bit is zero for SD */
	snd_hdac_ext_link_stream_clear(stream);
	/* program the stream_tag */
	val = readl(stream->pplc_addr + AZX_REG_PPLCCTL);
	val = (val & ~AZX_PPLCCTL_STRM_MASK) |
		(hstream->stream_tag << AZX_PPLCCTL_STRM_SHIFT);
	writel(val, stream->pplc_addr + AZX_REG_PPLCCTL);

	/* program the stream format */
	writew(fmt, stream->pplc_addr + AZX_REG_PPLCFMT);

	return 0;
}
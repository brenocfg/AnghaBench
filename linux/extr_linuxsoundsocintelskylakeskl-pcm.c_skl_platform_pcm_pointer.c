#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  runtime; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {scalar_t__ remap_addr; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;
struct TYPE_3__ {int index; unsigned int bufsize; } ;

/* Variables and functions */
 scalar_t__ AZX_REG_VS_SDXDPIB_XBASE ; 
 int AZX_REG_VS_SDXDPIB_XINTERVAL ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,unsigned int) ; 
 struct hdac_bus* get_bus_ctx (struct snd_pcm_substream*) ; 
 struct hdac_ext_stream* get_hdac_ext_stream (struct snd_pcm_substream*) ; 
 TYPE_1__* hdac_stream (struct hdac_ext_stream*) ; 
 unsigned int readl (scalar_t__) ; 
 unsigned int snd_hdac_stream_get_pos_posbuf (TYPE_1__*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static snd_pcm_uframes_t skl_platform_pcm_pointer
			(struct snd_pcm_substream *substream)
{
	struct hdac_ext_stream *hstream = get_hdac_ext_stream(substream);
	struct hdac_bus *bus = get_bus_ctx(substream);
	unsigned int pos;

	/*
	 * Use DPIB for Playback stream as the periodic DMA Position-in-
	 * Buffer Writes may be scheduled at the same time or later than
	 * the MSI and does not guarantee to reflect the Position of the
	 * last buffer that was transferred. Whereas DPIB register in
	 * HAD space reflects the actual data that is transferred.
	 * Use the position buffer for capture, as DPIB write gets
	 * completed earlier than the actual data written to the DDR.
	 *
	 * For capture stream following workaround is required to fix the
	 * incorrect position reporting.
	 *
	 * 1. Wait for 20us before reading the DMA position in buffer once
	 * the interrupt is generated for stream completion as update happens
	 * on the HDA frame boundary i.e. 20.833uSec.
	 * 2. Read DPIB register to flush the DMA position value. This dummy
	 * read is required to flush DMA position value.
	 * 3. Read the DMA Position-in-Buffer. This value now will be equal to
	 * or greater than period boundary.
	 */

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		pos = readl(bus->remap_addr + AZX_REG_VS_SDXDPIB_XBASE +
				(AZX_REG_VS_SDXDPIB_XINTERVAL *
				hdac_stream(hstream)->index));
	} else {
		udelay(20);
		readl(bus->remap_addr +
				AZX_REG_VS_SDXDPIB_XBASE +
				(AZX_REG_VS_SDXDPIB_XINTERVAL *
				 hdac_stream(hstream)->index));
		pos = snd_hdac_stream_get_pos_posbuf(hdac_stream(hstream));
	}

	if (pos >= hdac_stream(hstream)->bufsize)
		pos = 0;

	return bytes_to_frames(substream->runtime, pos);
}
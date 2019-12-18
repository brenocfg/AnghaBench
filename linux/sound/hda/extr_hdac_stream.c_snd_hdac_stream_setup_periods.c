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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int rate; } ;
struct TYPE_2__ {scalar_t__ area; } ;
struct hdac_stream {int period_bytes; int bufsize; int /*<<< orphan*/  no_period_wakeup; scalar_t__ frags; TYPE_1__ bdl; struct snd_pcm_substream* substream; struct hdac_bus* bus; } ;
struct hdac_bus {int bdl_pos_adj; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SD_BDLPL ; 
 int /*<<< orphan*/  SD_BDLPU ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int setup_bdle (struct hdac_bus*,int /*<<< orphan*/ ,struct hdac_stream*,int /*<<< orphan*/ **,int,int,int) ; 
 int /*<<< orphan*/  snd_hdac_stream_writel (struct hdac_stream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_get_dma_buf (struct snd_pcm_substream*) ; 

int snd_hdac_stream_setup_periods(struct hdac_stream *azx_dev)
{
	struct hdac_bus *bus = azx_dev->bus;
	struct snd_pcm_substream *substream = azx_dev->substream;
	struct snd_pcm_runtime *runtime = substream->runtime;
	__le32 *bdl;
	int i, ofs, periods, period_bytes;
	int pos_adj, pos_align;

	/* reset BDL address */
	snd_hdac_stream_writel(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_writel(azx_dev, SD_BDLPU, 0);

	period_bytes = azx_dev->period_bytes;
	periods = azx_dev->bufsize / period_bytes;

	/* program the initial BDL entries */
	bdl = (__le32 *)azx_dev->bdl.area;
	ofs = 0;
	azx_dev->frags = 0;

	pos_adj = bus->bdl_pos_adj;
	if (!azx_dev->no_period_wakeup && pos_adj > 0) {
		pos_align = pos_adj;
		pos_adj = (pos_adj * runtime->rate + 47999) / 48000;
		if (!pos_adj)
			pos_adj = pos_align;
		else
			pos_adj = ((pos_adj + pos_align - 1) / pos_align) *
				pos_align;
		pos_adj = frames_to_bytes(runtime, pos_adj);
		if (pos_adj >= period_bytes) {
			dev_warn(bus->dev, "Too big adjustment %d\n",
				 pos_adj);
			pos_adj = 0;
		} else {
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev,
					 &bdl, ofs, pos_adj, true);
			if (ofs < 0)
				goto error;
		}
	} else
		pos_adj = 0;

	for (i = 0; i < periods; i++) {
		if (i == periods - 1 && pos_adj)
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev, &bdl, ofs,
					 period_bytes - pos_adj, 0);
		else
			ofs = setup_bdle(bus, snd_pcm_get_dma_buf(substream),
					 azx_dev, &bdl, ofs,
					 period_bytes,
					 !azx_dev->no_period_wakeup);
		if (ofs < 0)
			goto error;
	}
	return 0;

 error:
	dev_err(bus->dev, "Too many BDL entries: buffer=%d, period=%d\n",
		azx_dev->bufsize, period_bytes);
	return -EINVAL;
}
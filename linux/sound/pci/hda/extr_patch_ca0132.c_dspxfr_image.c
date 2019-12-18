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
struct hda_codec {struct ca0132_spec* spec; } ;
struct dsp_image_seg {int dummy; } ;
struct dma_engine {unsigned short m_converter_format; int buf_size; struct dma_engine* dmab; scalar_t__ area; struct hda_codec* codec; } ;
struct ca0132_spec {int dsp_stream_id; } ;

/* Variables and functions */
 int DSP_DMA_WRITE_BUFLEN_INIT ; 
 int DSP_DMA_WRITE_BUFLEN_OVLY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int INVALID_DMA_CHANNEL ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  codec_dbg (struct hda_codec*,char*) ; 
 int codec_set_converter_format (struct hda_codec*,int /*<<< orphan*/ ,unsigned short,unsigned int*) ; 
 int codec_set_converter_stream_channel (struct hda_codec*,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  dma_convert_to_hda_format (struct hda_codec*,unsigned int,unsigned short,unsigned short*) ; 
 unsigned char dma_get_stream_id (struct dma_engine*) ; 
 int dsp_allocate_ports_format (struct hda_codec*,unsigned short,unsigned int*) ; 
 int dsp_free_ports (struct hda_codec*) ; 
 int dspio_alloc_dma_chan (struct hda_codec*,unsigned int*) ; 
 int /*<<< orphan*/  dspio_free_dma_chan (struct hda_codec*,unsigned int) ; 
 int dspxfr_one_seg (struct hda_codec*,struct dsp_image_seg const*,unsigned int,struct dma_engine*,unsigned int,unsigned int,int) ; 
 struct dsp_image_seg* get_next_seg_ptr (struct dsp_image_seg const*) ; 
 scalar_t__ is_hci_prog_list_seg (struct dsp_image_seg const*) ; 
 int /*<<< orphan*/  is_last (struct dsp_image_seg const*) ; 
 int /*<<< orphan*/  is_valid (struct dsp_image_seg const*) ; 
 int /*<<< orphan*/  kfree (struct dma_engine*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_load_dsp_cleanup (struct hda_codec*,struct dma_engine*) ; 
 int snd_hda_codec_load_dsp_prepare (struct hda_codec*,unsigned short,int,struct dma_engine*) ; 

__attribute__((used)) static int dspxfr_image(struct hda_codec *codec,
			const struct dsp_image_seg *fls_data,
			unsigned int reloc,
			unsigned int sample_rate,
			unsigned short channels,
			bool ovly)
{
	struct ca0132_spec *spec = codec->spec;
	int status;
	unsigned short hda_format = 0;
	unsigned int response;
	unsigned char stream_id = 0;
	struct dma_engine *dma_engine;
	unsigned int dma_chan;
	unsigned int port_map_mask;

	if (fls_data == NULL)
		return -EINVAL;

	dma_engine = kzalloc(sizeof(*dma_engine), GFP_KERNEL);
	if (!dma_engine)
		return -ENOMEM;

	dma_engine->dmab = kzalloc(sizeof(*dma_engine->dmab), GFP_KERNEL);
	if (!dma_engine->dmab) {
		kfree(dma_engine);
		return -ENOMEM;
	}

	dma_engine->codec = codec;
	dma_convert_to_hda_format(codec, sample_rate, channels, &hda_format);
	dma_engine->m_converter_format = hda_format;
	dma_engine->buf_size = (ovly ? DSP_DMA_WRITE_BUFLEN_OVLY :
			DSP_DMA_WRITE_BUFLEN_INIT) * 2;

	dma_chan = ovly ? INVALID_DMA_CHANNEL : 0;

	status = codec_set_converter_format(codec, WIDGET_CHIP_CTRL,
					hda_format, &response);

	if (status < 0) {
		codec_dbg(codec, "set converter format fail\n");
		goto exit;
	}

	status = snd_hda_codec_load_dsp_prepare(codec,
				dma_engine->m_converter_format,
				dma_engine->buf_size,
				dma_engine->dmab);
	if (status < 0)
		goto exit;
	spec->dsp_stream_id = status;

	if (ovly) {
		status = dspio_alloc_dma_chan(codec, &dma_chan);
		if (status < 0) {
			codec_dbg(codec, "alloc dmachan fail\n");
			dma_chan = INVALID_DMA_CHANNEL;
			goto exit;
		}
	}

	port_map_mask = 0;
	status = dsp_allocate_ports_format(codec, hda_format,
					&port_map_mask);
	if (status < 0) {
		codec_dbg(codec, "alloc ports fail\n");
		goto exit;
	}

	stream_id = dma_get_stream_id(dma_engine);
	status = codec_set_converter_stream_channel(codec,
			WIDGET_CHIP_CTRL, stream_id, 0, &response);
	if (status < 0) {
		codec_dbg(codec, "set stream chan fail\n");
		goto exit;
	}

	while ((fls_data != NULL) && !is_last(fls_data)) {
		if (!is_valid(fls_data)) {
			codec_dbg(codec, "FLS check fail\n");
			status = -EINVAL;
			goto exit;
		}
		status = dspxfr_one_seg(codec, fls_data, reloc,
					dma_engine, dma_chan,
					port_map_mask, ovly);
		if (status < 0)
			break;

		if (is_hci_prog_list_seg(fls_data))
			fls_data = get_next_seg_ptr(fls_data);

		if ((fls_data != NULL) && !is_last(fls_data))
			fls_data = get_next_seg_ptr(fls_data);
	}

	if (port_map_mask != 0)
		status = dsp_free_ports(codec);

	if (status < 0)
		goto exit;

	status = codec_set_converter_stream_channel(codec,
				WIDGET_CHIP_CTRL, 0, 0, &response);

exit:
	if (ovly && (dma_chan != INVALID_DMA_CHANNEL))
		dspio_free_dma_chan(codec, dma_chan);

	if (dma_engine->dmab->area)
		snd_hda_codec_load_dsp_cleanup(codec, dma_engine->dmab);
	kfree(dma_engine->dmab);
	kfree(dma_engine);

	return status;
}
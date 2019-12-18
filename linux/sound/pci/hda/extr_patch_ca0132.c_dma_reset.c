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
struct hda_codec {struct ca0132_spec* spec; } ;
struct dma_engine {TYPE_1__* dmab; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  m_converter_format; struct hda_codec* codec; } ;
struct ca0132_spec {int dsp_stream_id; } ;
struct TYPE_3__ {scalar_t__ area; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_codec_load_dsp_cleanup (struct hda_codec*,TYPE_1__*) ; 
 int snd_hda_codec_load_dsp_prepare (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int dma_reset(struct dma_engine *dma)
{
	struct hda_codec *codec = dma->codec;
	struct ca0132_spec *spec = codec->spec;
	int status;

	if (dma->dmab->area)
		snd_hda_codec_load_dsp_cleanup(codec, dma->dmab);

	status = snd_hda_codec_load_dsp_prepare(codec,
			dma->m_converter_format,
			dma->buf_size,
			dma->dmab);
	if (status < 0)
		return status;
	spec->dsp_stream_id = status;
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct sst_runtime_stream {int id; TYPE_9__* compr_ops; } ;
struct sst_data {int dummy; } ;
struct sst_compress_cb {int /*<<< orphan*/  drain_notify; struct snd_compr_stream* drain_cb_param; int /*<<< orphan*/  compr_cb; struct snd_compr_stream* param; } ;
struct TYPE_18__ {int sg_count; int /*<<< orphan*/  frag_size; TYPE_6__* ring_buf_info; } ;
struct TYPE_13__ {int pcm_wd_sz; int /*<<< orphan*/  externalsr; int /*<<< orphan*/  bs_format; int /*<<< orphan*/  num_chan; } ;
struct TYPE_12__ {int pcm_wd_sz; int /*<<< orphan*/  num_chan; } ;
struct TYPE_14__ {TYPE_2__ aac_params; TYPE_1__ mp3_params; } ;
struct TYPE_15__ {TYPE_3__ uc; } ;
struct snd_sst_params {TYPE_7__ aparams; TYPE_4__ sparams; int /*<<< orphan*/  codec; } ;
struct snd_soc_pcm_runtime {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct snd_compr_stream {TYPE_8__* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_16__ {int id; int format; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  ch_in; } ;
struct snd_compr_params {TYPE_5__ codec; } ;
typedef  int /*<<< orphan*/  str_params ;
struct TYPE_20__ {int (* open ) (int /*<<< orphan*/ ,struct snd_sst_params*,struct sst_compress_cb*) ;} ;
struct TYPE_19__ {int /*<<< orphan*/  fragment_size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  buffer; struct sst_runtime_stream* private_data; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_BIT_STREAM_ADTS ; 
 int /*<<< orphan*/  AAC_BIT_STREAM_RAW ; 
 int /*<<< orphan*/  DRV_NAME ; 
 int EINVAL ; 
#define  SND_AUDIOCODEC_AAC 129 
#define  SND_AUDIOCODEC_MP3 128 
 int SND_AUDIOSTREAMFORMAT_MP4ADTS ; 
 int SND_AUDIOSTREAMFORMAT_RAW ; 
 int /*<<< orphan*/  SST_CODEC_TYPE_AAC ; 
 int /*<<< orphan*/  SST_CODEC_TYPE_MP3 ; 
 int /*<<< orphan*/  memset (struct snd_sst_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 struct sst_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_rtdcom_lookup (struct snd_soc_pcm_runtime*,int /*<<< orphan*/ ) ; 
 TYPE_10__* sst ; 
 int /*<<< orphan*/  sst_compr_fragment_elapsed ; 
 int /*<<< orphan*/  sst_drain_notify ; 
 int sst_fill_stream_params (struct snd_compr_stream*,struct sst_data*,struct snd_sst_params*,int) ; 
 int stub1 (int /*<<< orphan*/ ,struct snd_sst_params*,struct sst_compress_cb*) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sst_platform_compr_set_params(struct snd_compr_stream *cstream,
					struct snd_compr_params *params)
{
	struct sst_runtime_stream *stream;
	int retval;
	struct snd_sst_params str_params;
	struct sst_compress_cb cb;
	struct snd_soc_pcm_runtime *rtd = cstream->private_data;
	struct snd_soc_component *component = snd_soc_rtdcom_lookup(rtd, DRV_NAME);
	struct sst_data *ctx = snd_soc_component_get_drvdata(component);

	stream = cstream->runtime->private_data;
	/* construct fw structure for this*/
	memset(&str_params, 0, sizeof(str_params));

	/* fill the device type and stream id to pass to SST driver */
	retval = sst_fill_stream_params(cstream, ctx, &str_params, true);
	pr_debug("compr_set_params: fill stream params ret_val = 0x%x\n", retval);
	if (retval < 0)
		return retval;

	switch (params->codec.id) {
	case SND_AUDIOCODEC_MP3: {
		str_params.codec = SST_CODEC_TYPE_MP3;
		str_params.sparams.uc.mp3_params.num_chan = params->codec.ch_in;
		str_params.sparams.uc.mp3_params.pcm_wd_sz = 16;
		break;
	}

	case SND_AUDIOCODEC_AAC: {
		str_params.codec = SST_CODEC_TYPE_AAC;
		str_params.sparams.uc.aac_params.num_chan = params->codec.ch_in;
		str_params.sparams.uc.aac_params.pcm_wd_sz = 16;
		if (params->codec.format == SND_AUDIOSTREAMFORMAT_MP4ADTS)
			str_params.sparams.uc.aac_params.bs_format =
							AAC_BIT_STREAM_ADTS;
		else if (params->codec.format == SND_AUDIOSTREAMFORMAT_RAW)
			str_params.sparams.uc.aac_params.bs_format =
							AAC_BIT_STREAM_RAW;
		else {
			pr_err("Undefined format%d\n", params->codec.format);
			return -EINVAL;
		}
		str_params.sparams.uc.aac_params.externalsr =
						params->codec.sample_rate;
		break;
	}

	default:
		pr_err("codec not supported, id =%d\n", params->codec.id);
		return -EINVAL;
	}

	str_params.aparams.ring_buf_info[0].addr  =
					virt_to_phys(cstream->runtime->buffer);
	str_params.aparams.ring_buf_info[0].size =
					cstream->runtime->buffer_size;
	str_params.aparams.sg_count = 1;
	str_params.aparams.frag_size = cstream->runtime->fragment_size;

	cb.param = cstream;
	cb.compr_cb = sst_compr_fragment_elapsed;
	cb.drain_cb_param = cstream;
	cb.drain_notify = sst_drain_notify;

	retval = stream->compr_ops->open(sst->dev, &str_params, &cb);
	if (retval < 0) {
		pr_err("stream allocation failed %d\n", retval);
		return retval;
	}

	stream->id = retval;
	return 0;
}
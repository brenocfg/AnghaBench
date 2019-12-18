#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct spdifContext {int codec_id; int need_close; int /*<<< orphan*/  fmt; int /*<<< orphan*/  sstride; int /*<<< orphan*/  use_dts_hd; TYPE_3__* lavf_ctx; } ;
struct mp_filter {struct spdifContext* priv; } ;
struct mp_chmap {int dummy; } ;
struct TYPE_12__ {int direct; } ;
struct TYPE_11__ {TYPE_4__* pb; int /*<<< orphan*/  oformat; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int codec_id; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AF_FORMAT_S_AAC ; 
 int AF_FORMAT_S_AC3 ; 
 int AF_FORMAT_S_DTS ; 
 int AF_FORMAT_S_DTSHD ; 
 int AF_FORMAT_S_EAC3 ; 
 int AF_FORMAT_S_MP3 ; 
 int AF_FORMAT_S_TRUEHD ; 
#define  AV_CODEC_ID_AAC 133 
#define  AV_CODEC_ID_AC3 132 
#define  AV_CODEC_ID_DTS 131 
#define  AV_CODEC_ID_EAC3 130 
#define  AV_CODEC_ID_MP3 129 
#define  AV_CODEC_ID_TRUEHD 128 
 int FF_PROFILE_DTS_HD_HRA ; 
 int FF_PROFILE_DTS_HD_MA ; 
 int FF_PROFILE_UNKNOWN ; 
 int /*<<< orphan*/  MP_FATAL (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct mp_filter*,char*,int,int) ; 
 int /*<<< orphan*/  OUTBUF_SIZE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (void*) ; 
 int /*<<< orphan*/  av_guess_format (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* av_mallocz (int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_alloc_context () ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ avformat_write_header (TYPE_3__*,int /*<<< orphan*/ **) ; 
 TYPE_4__* avio_alloc_context (void*,int /*<<< orphan*/ ,int,struct spdifContext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy (struct mp_filter*) ; 
 int /*<<< orphan*/  determine_codec_params (struct mp_filter*,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  mp_aframe_create () ; 
 int /*<<< orphan*/  mp_aframe_get_sstride (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_aframe_set_chmap (int /*<<< orphan*/ ,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_aframe_set_format (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_aframe_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mp_chmap_from_channels (struct mp_chmap*,int) ; 
 int /*<<< orphan*/  mp_filter_internal_mark_failed (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_steal (struct spdifContext*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_packet ; 

__attribute__((used)) static int init_filter(struct mp_filter *da, AVPacket *pkt)
{
    struct spdifContext *spdif_ctx = da->priv;

    int profile = FF_PROFILE_UNKNOWN;
    int c_rate = 0;
    determine_codec_params(da, pkt, &profile, &c_rate);
    MP_VERBOSE(da, "In: profile=%d samplerate=%d\n", profile, c_rate);

    AVFormatContext *lavf_ctx  = avformat_alloc_context();
    if (!lavf_ctx)
        goto fail;

    spdif_ctx->lavf_ctx = lavf_ctx;

    lavf_ctx->oformat = av_guess_format("spdif", NULL, NULL);
    if (!lavf_ctx->oformat)
        goto fail;

    void *buffer = av_mallocz(OUTBUF_SIZE);
    if (!buffer)
        abort();
    lavf_ctx->pb = avio_alloc_context(buffer, OUTBUF_SIZE, 1, spdif_ctx, NULL,
                                      write_packet, NULL);
    if (!lavf_ctx->pb) {
        av_free(buffer);
        goto fail;
    }

    // Request minimal buffering (not available on Libav)
#if LIBAVFORMAT_VERSION_MICRO >= 100
    lavf_ctx->pb->direct = 1;
#endif

    AVStream *stream = avformat_new_stream(lavf_ctx, 0);
    if (!stream)
        goto fail;

    stream->codecpar->codec_id = spdif_ctx->codec_id;

    AVDictionary *format_opts = NULL;

    spdif_ctx->fmt = mp_aframe_create();
    talloc_steal(spdif_ctx, spdif_ctx->fmt);

    int num_channels = 0;
    int sample_format = 0;
    int samplerate = 0;
    switch (spdif_ctx->codec_id) {
    case AV_CODEC_ID_AAC:
        sample_format                   = AF_FORMAT_S_AAC;
        samplerate                      = 48000;
        num_channels                    = 2;
        break;
    case AV_CODEC_ID_AC3:
        sample_format                   = AF_FORMAT_S_AC3;
        samplerate                      = c_rate > 0 ? c_rate : 48000;
        num_channels                    = 2;
        break;
    case AV_CODEC_ID_DTS: {
        bool is_hd = profile == FF_PROFILE_DTS_HD_HRA ||
                     profile == FF_PROFILE_DTS_HD_MA  ||
                     profile == FF_PROFILE_UNKNOWN;

        // Apparently, DTS-HD over SPDIF is specified to be 7.1 (8 channels)
        // for DTS-HD MA, and stereo (2 channels) for DTS-HD HRA. The bit
        // streaming rate as well as the signaled channel count are defined
        // based on this value.
        int dts_hd_spdif_channel_count = profile == FF_PROFILE_DTS_HD_HRA ?
                                         2 : 8;
        if (spdif_ctx->use_dts_hd && is_hd) {
            av_dict_set_int(&format_opts, "dtshd_rate",
                            dts_hd_spdif_channel_count * 96000, 0);
            sample_format               = AF_FORMAT_S_DTSHD;
            samplerate                  = 192000;
            num_channels                = dts_hd_spdif_channel_count;
        } else {
            sample_format               = AF_FORMAT_S_DTS;
            samplerate                  = 48000;
            num_channels                = 2;
        }
        break;
    }
    case AV_CODEC_ID_EAC3:
        sample_format                   = AF_FORMAT_S_EAC3;
        samplerate                      = 192000;
        num_channels                    = 2;
        break;
    case AV_CODEC_ID_MP3:
        sample_format                   = AF_FORMAT_S_MP3;
        samplerate                      = 48000;
        num_channels                    = 2;
        break;
    case AV_CODEC_ID_TRUEHD:
        sample_format                   = AF_FORMAT_S_TRUEHD;
        samplerate                      = 192000;
        num_channels                    = 8;
        break;
    default:
        abort();
    }

    struct mp_chmap chmap;
    mp_chmap_from_channels(&chmap, num_channels);
    mp_aframe_set_chmap(spdif_ctx->fmt, &chmap);
    mp_aframe_set_format(spdif_ctx->fmt, sample_format);
    mp_aframe_set_rate(spdif_ctx->fmt, samplerate);

    spdif_ctx->sstride = mp_aframe_get_sstride(spdif_ctx->fmt);

    if (avformat_write_header(lavf_ctx, &format_opts) < 0) {
        MP_FATAL(da, "libavformat spdif initialization failed.\n");
        av_dict_free(&format_opts);
        goto fail;
    }
    av_dict_free(&format_opts);

    spdif_ctx->need_close = true;

    return 0;

fail:
    destroy(da);
    mp_filter_internal_mark_failed(da);
    return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_16__ ;
typedef  struct TYPE_30__   TYPE_13__ ;

/* Type definitions */
struct TYPE_34__ {TYPE_2__* tv_param; int /*<<< orphan*/  priv; TYPE_4__* functions; TYPE_6__* demuxer; int /*<<< orphan*/  path; TYPE_1__* info; } ;
typedef  TYPE_3__ tvi_handle_t ;
struct TYPE_35__ {scalar_t__ (* control ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_4__ tvi_functions_t ;
struct TYPE_36__ {int /*<<< orphan*/  input; int /*<<< orphan*/  channel; } ;
typedef  TYPE_5__ tv_param_t ;
struct sh_stream {TYPE_13__* codec; } ;
typedef  enum demux_check { ____Placeholder_demux_check } demux_check ;
struct TYPE_37__ {int extended_ctrls; scalar_t__ seekable; TYPE_3__* priv; int /*<<< orphan*/  log; TYPE_3__* stream; int /*<<< orphan*/  global; } ;
typedef  TYPE_6__ demuxer_t ;
struct TYPE_38__ {scalar_t__ len; } ;
typedef  TYPE_7__ bstr ;
struct TYPE_33__ {float fps; int immediate; float audiorate; int gain; int /*<<< orphan*/  contrast; int /*<<< orphan*/  saturation; int /*<<< orphan*/  hue; int /*<<< orphan*/  brightness; scalar_t__ audio; } ;
struct TYPE_32__ {int /*<<< orphan*/  name; } ;
struct TYPE_31__ {int num; } ;
struct TYPE_30__ {char* codec; int codec_tag; float fps; float disp_w; float disp_h; int samplerate; TYPE_16__ channels; } ;

/* Variables and functions */
#define  AF_FORMAT_S16 128 
 scalar_t__ BIG_ENDIAN ; 
 int /*<<< orphan*/  BSTR_P (TYPE_7__) ; 
 scalar_t__ BYTE_ORDER ; 
 int DEMUX_CHECK_REQUEST ; 
 int /*<<< orphan*/  MP_ERR (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int MP_FOURCC_JPEG ; 
 int MP_FOURCC_MJPEG ; 
 int /*<<< orphan*/  MP_VERBOSE (TYPE_3__*,char*,int,int,int) ; 
 int /*<<< orphan*/  MP_WARN (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  STREAM_AUDIO ; 
 int /*<<< orphan*/  STREAM_VIDEO ; 
 int /*<<< orphan*/  TVI_CONTROL_AUD_GET_CHANNELS ; 
 int /*<<< orphan*/  TVI_CONTROL_AUD_GET_FORMAT ; 
 int /*<<< orphan*/  TVI_CONTROL_AUD_GET_SAMPLERATE ; 
 int /*<<< orphan*/  TVI_CONTROL_AUD_SET_SAMPLERATE ; 
 int /*<<< orphan*/  TVI_CONTROL_IMMEDIATE ; 
 int /*<<< orphan*/  TVI_CONTROL_IS_AUDIO ; 
 scalar_t__ TVI_CONTROL_TRUE ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_FORMAT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_FPS ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_HEIGHT ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_GET_WIDTH ; 
 int /*<<< orphan*/  TVI_CONTROL_VID_SET_GAIN ; 
 int /*<<< orphan*/  TV_COLOR_BRIGHTNESS ; 
 int /*<<< orphan*/  TV_COLOR_CONTRAST ; 
 int /*<<< orphan*/  TV_COLOR_HUE ; 
 int /*<<< orphan*/  TV_COLOR_SATURATION ; 
 int /*<<< orphan*/  af_fmt_to_str (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_7__ bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bstr_split_tok (TYPE_7__,char*,TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  bstrto0 (int /*<<< orphan*/ *,TYPE_7__) ; 
 int /*<<< orphan*/  bstrtoll (TYPE_7__,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demux_add_sh_stream (TYPE_6__*,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_from_channels (TYPE_16__*,int) ; 
 TYPE_5__* mp_get_config_group (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_set_pcm_codec (TYPE_13__*,int,int,int,int) ; 
 int /*<<< orphan*/  open_tv (TYPE_3__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ) ; 
 scalar_t__ stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 
 TYPE_3__* tv_begin (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_params_conf ; 
 int /*<<< orphan*/  tv_set_color_options (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tv_uninit (TYPE_3__*) ; 

__attribute__((used)) static int demux_open_tv(demuxer_t *demuxer, enum demux_check check)
{
    tvi_handle_t *tvh;
    const tvi_functions_t *funcs;

    if (check > DEMUX_CHECK_REQUEST)
        return -1;

    if (!demuxer->stream->info || strcmp(demuxer->stream->info->name, "tv") != 0)
        return -1;

    tv_param_t *params = mp_get_config_group(demuxer, demuxer->global,
                                             &tv_params_conf);
    bstr urlparams = bstr0(demuxer->stream->path);
    bstr channel, input;
    bstr_split_tok(urlparams, "/", &channel, &input);
    if (channel.len) {
        talloc_free(params->channel);
        params->channel = bstrto0(NULL, channel);
    }
    if (input.len) {
        bstr r;
        params->input = bstrtoll(input, &r, 0);
        if (r.len) {
            MP_ERR(demuxer->stream, "invalid input: '%.*s'\n", BSTR_P(input));
            return -1;
        }
    }

    assert(demuxer->priv==NULL);
    if(!(tvh=tv_begin(params, demuxer->log))) return -1;
    if (!tvh->functions->init(tvh->priv)) return -1;

    tvh->demuxer = demuxer;

    if (!open_tv(tvh)){
        tv_uninit(tvh);
        return -1;
    }
    funcs = tvh->functions;
    demuxer->priv=tvh;

    struct sh_stream *sh_v = demux_alloc_sh_stream(STREAM_VIDEO);

    /* get IMAGE FORMAT */
    int fourcc;
    funcs->control(tvh->priv, TVI_CONTROL_VID_GET_FORMAT, &fourcc);
    if (fourcc == MP_FOURCC_MJPEG || fourcc == MP_FOURCC_JPEG) {
        sh_v->codec->codec = "mjpeg";
    } else {
        sh_v->codec->codec = "rawvideo";
        sh_v->codec->codec_tag = fourcc;
    }

    /* set FPS and FRAMETIME */

    if(!sh_v->codec->fps)
    {
        float tmp;
        if (funcs->control(tvh->priv, TVI_CONTROL_VID_GET_FPS, &tmp) != TVI_CONTROL_TRUE)
             sh_v->codec->fps = 25.0f; /* on PAL */
        else sh_v->codec->fps = tmp;
    }

    if (tvh->tv_param->fps != -1.0f)
        sh_v->codec->fps = tvh->tv_param->fps;

    /* If playback only mode, go to immediate mode, fail silently */
    if(tvh->tv_param->immediate == 1)
        {
        funcs->control(tvh->priv, TVI_CONTROL_IMMEDIATE, 0);
        tvh->tv_param->audio = 0;
        }

    /* set width */
    funcs->control(tvh->priv, TVI_CONTROL_VID_GET_WIDTH, &sh_v->codec->disp_w);

    /* set height */
    funcs->control(tvh->priv, TVI_CONTROL_VID_GET_HEIGHT, &sh_v->codec->disp_h);

    demux_add_sh_stream(demuxer, sh_v);

    demuxer->seekable = 0;

    /* here comes audio init */
    if (tvh->tv_param->audio && funcs->control(tvh->priv, TVI_CONTROL_IS_AUDIO, 0) == TVI_CONTROL_TRUE)
    {
        int audio_format;

        /* yeah, audio is present */

        funcs->control(tvh->priv, TVI_CONTROL_AUD_SET_SAMPLERATE,
                                  &tvh->tv_param->audiorate);

        if (funcs->control(tvh->priv, TVI_CONTROL_AUD_GET_FORMAT, &audio_format) != TVI_CONTROL_TRUE)
            goto no_audio;

        switch(audio_format)
        {
            // This is the only format any of the current inputs generate.
            case AF_FORMAT_S16:
                break;
            default:
                MP_ERR(tvh, "Audio type '%s' unsupported!\n",
                    af_fmt_to_str(audio_format));
                goto no_audio;
        }

        struct sh_stream *sh_a = demux_alloc_sh_stream(STREAM_AUDIO);

        funcs->control(tvh->priv, TVI_CONTROL_AUD_GET_SAMPLERATE,
                   &sh_a->codec->samplerate);
        int nchannels = sh_a->codec->channels.num;
        funcs->control(tvh->priv, TVI_CONTROL_AUD_GET_CHANNELS,
                   &nchannels);
        mp_chmap_from_channels(&sh_a->codec->channels, nchannels);

        // s16ne
        mp_set_pcm_codec(sh_a->codec, true, false, 16, BYTE_ORDER == BIG_ENDIAN);

        demux_add_sh_stream(demuxer, sh_a);

        MP_VERBOSE(tvh, "  TV audio: %d channels, %d bits, %d Hz\n",
                   nchannels, 16, sh_a->codec->samplerate);
    }
no_audio:

    if(!(funcs->start(tvh->priv))){
        // start failed :(
        tv_uninit(tvh);
        return -1;
    }

    /* set color eq */
    tv_set_color_options(tvh, TV_COLOR_BRIGHTNESS, tvh->tv_param->brightness);
    tv_set_color_options(tvh, TV_COLOR_HUE, tvh->tv_param->hue);
    tv_set_color_options(tvh, TV_COLOR_SATURATION, tvh->tv_param->saturation);
    tv_set_color_options(tvh, TV_COLOR_CONTRAST, tvh->tv_param->contrast);

    if(tvh->tv_param->gain!=-1)
        if(funcs->control(tvh->priv,TVI_CONTROL_VID_SET_GAIN,&tvh->tv_param->gain)!=TVI_CONTROL_TRUE)
            MP_WARN(tvh, "Unable to set gain control!\n");

    demuxer->extended_ctrls = true;

    return 0;
}
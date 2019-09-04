#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_9__ ;
typedef  struct TYPE_41__   TYPE_8__ ;
typedef  struct TYPE_40__   TYPE_7__ ;
typedef  struct TYPE_39__   TYPE_6__ ;
typedef  struct TYPE_38__   TYPE_5__ ;
typedef  struct TYPE_37__   TYPE_4__ ;
typedef  struct TYPE_36__   TYPE_3__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_24__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct sh_stream {int default_track; int forced_track; int dependent_track; int visual_impaired_track; int hearing_impaired_track; int still_image; scalar_t__ hls_bitrate; int missing_timestamps; int /*<<< orphan*/  tags; void* title; void* lang; int /*<<< orphan*/  demuxer_id; TYPE_4__* codec; int /*<<< orphan*/  ff_index; TYPE_13__* attached_picture; } ;
struct mp_spherical_params {float* ref_angles; int /*<<< orphan*/  type; } ;
struct TYPE_36__ {scalar_t__ use_stream_ids; int /*<<< orphan*/  image_format; } ;
struct TYPE_38__ {int num_streams; int avif_flags; TYPE_3__ format_hack; int /*<<< orphan*/  streams; int /*<<< orphan*/  mf_fps; int /*<<< orphan*/  seek_delay; TYPE_10__* avfc; } ;
typedef  TYPE_5__ lavf_priv_t ;
struct TYPE_39__ {TYPE_5__* priv; } ;
typedef  TYPE_6__ demuxer_t ;
struct TYPE_42__ {int num; int den; } ;
struct TYPE_41__ {float yaw; float pitch; float roll; int /*<<< orphan*/  projection; } ;
struct TYPE_35__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_33__ {int /*<<< orphan*/  den; int /*<<< orphan*/  num; } ;
struct TYPE_34__ {int /*<<< orphan*/  num; } ;
struct TYPE_40__ {int disposition; int /*<<< orphan*/  metadata; int /*<<< orphan*/  id; TYPE_2__ time_base; int /*<<< orphan*/  index; TYPE_1__ sample_aspect_ratio; TYPE_24__ avg_frame_rate; int /*<<< orphan*/  attached_pic; TYPE_12__* codecpar; } ;
struct TYPE_37__ {int rotate; double frame_based; int /*<<< orphan*/  native_tb_den; int /*<<< orphan*/  native_tb_num; scalar_t__ lav_codecpar; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  avi_dts; struct mp_spherical_params spherical; int /*<<< orphan*/  par_h; int /*<<< orphan*/  par_w; int /*<<< orphan*/  fps; int /*<<< orphan*/  disp_h; int /*<<< orphan*/  disp_w; int /*<<< orphan*/  bitrate; scalar_t__ samplerate; int /*<<< orphan*/  channels; } ;
struct TYPE_32__ {int keyframe; int /*<<< orphan*/  pts; } ;
struct TYPE_31__ {int initial_padding; int codec_type; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  extradata_size; int /*<<< orphan*/  extradata; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ sample_rate; int /*<<< orphan*/  bit_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  channels; } ;
struct TYPE_30__ {char* value; } ;
struct TYPE_29__ {TYPE_7__** streams; } ;
typedef  TYPE_7__ AVStream ;
typedef  TYPE_8__ AVSphericalMapping ;
typedef  TYPE_9__ AVRational ;
typedef  TYPE_10__ AVFormatContext ;
typedef  TYPE_11__ AVDictionaryEntry ;
typedef  TYPE_12__ AVCodecParameters ;

/* Variables and functions */
 int AVFMT_NOTIMESTAMPS ; 
#define  AVMEDIA_TYPE_ATTACHMENT 131 
#define  AVMEDIA_TYPE_AUDIO 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int AV_DISPOSITION_ATTACHED_PIC ; 
 int AV_DISPOSITION_DEFAULT ; 
 int AV_DISPOSITION_DEPENDENT ; 
 int AV_DISPOSITION_FORCED ; 
 int AV_DISPOSITION_HEARING_IMPAIRED ; 
 int AV_DISPOSITION_STILL_IMAGE ; 
 int AV_DISPOSITION_TIMED_THUMBNAILS ; 
 int AV_DISPOSITION_VISUAL_IMPAIRED ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int /*<<< orphan*/  AV_PKT_DATA_DISPLAYMATRIX ; 
 int /*<<< orphan*/  AV_PKT_DATA_SPHERICAL ; 
 int /*<<< orphan*/  AV_SPHERICAL_EQUIRECTANGULAR ; 
 int /*<<< orphan*/  MPMAX (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  MP_SPHERICAL_EQUIRECTANGULAR ; 
 int /*<<< orphan*/  MP_SPHERICAL_UNKNOWN ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (TYPE_5__*,int /*<<< orphan*/ ,int,struct sh_stream*) ; 
 int /*<<< orphan*/  STREAM_AUDIO ; 
 int /*<<< orphan*/  STREAM_SUB ; 
 int /*<<< orphan*/  STREAM_VIDEO ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_11__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double av_display_rotation_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_opt_get_q (TYPE_10__*,char*,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  av_q2d (TYPE_24__) ; 
 int /*<<< orphan*/ * av_stream_get_side_data (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_parameters_alloc () ; 
 int /*<<< orphan*/  avcodec_parameters_copy (scalar_t__,TYPE_12__*) ; 
 int /*<<< orphan*/  demux_add_sh_stream (TYPE_6__*,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  demuxer_add_attachment (TYPE_6__*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dict_get_decimal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  export_replaygain (TYPE_6__*,struct sh_stream*,TYPE_7__*) ; 
 int /*<<< orphan*/  isnan (double) ; 
 int /*<<< orphan*/  matches_avinputformat_name (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_from_lavc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_chmap_set_unknown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_codec_from_av_codec_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_tags_copy_from_av_dictionary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_13__* new_demux_packet_from_avpacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  select_tracks (TYPE_6__*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* talloc_asprintf (struct sh_stream*,char*,...) ; 
 int /*<<< orphan*/  talloc_size (struct sh_stream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_steal (struct sh_stream*,TYPE_13__*) ; 
 void* talloc_strdup (struct sh_stream*,char*) ; 

__attribute__((used)) static void handle_new_stream(demuxer_t *demuxer, int i)
{
    lavf_priv_t *priv = demuxer->priv;
    AVFormatContext *avfc = priv->avfc;
    AVStream *st = avfc->streams[i];
    struct sh_stream *sh = NULL;
    AVCodecParameters *codec = st->codecpar;
    int lavc_delay = codec->initial_padding;

    switch (codec->codec_type) {
    case AVMEDIA_TYPE_AUDIO: {
        sh = demux_alloc_sh_stream(STREAM_AUDIO);

        // probably unneeded
        mp_chmap_set_unknown(&sh->codec->channels, codec->channels);
        if (codec->channel_layout)
            mp_chmap_from_lavc(&sh->codec->channels, codec->channel_layout);
        sh->codec->samplerate = codec->sample_rate;
        sh->codec->bitrate = codec->bit_rate;

        double delay = 0;
        if (codec->sample_rate > 0)
            delay = lavc_delay / (double)codec->sample_rate;
        priv->seek_delay = MPMAX(priv->seek_delay, delay);

        export_replaygain(demuxer, sh, st);

        break;
    }
    case AVMEDIA_TYPE_VIDEO: {
        sh = demux_alloc_sh_stream(STREAM_VIDEO);

        if ((st->disposition & AV_DISPOSITION_ATTACHED_PIC) &&
            !(st->disposition & AV_DISPOSITION_TIMED_THUMBNAILS))
        {
            sh->attached_picture =
                new_demux_packet_from_avpacket(&st->attached_pic);
            if (sh->attached_picture) {
                sh->attached_picture->pts = 0;
                talloc_steal(sh, sh->attached_picture);
                sh->attached_picture->keyframe = true;
            }
        }

        sh->codec->disp_w = codec->width;
        sh->codec->disp_h = codec->height;
        if (st->avg_frame_rate.num)
            sh->codec->fps = av_q2d(st->avg_frame_rate);
        if (priv->format_hack.image_format)
            sh->codec->fps = priv->mf_fps;
        sh->codec->par_w = st->sample_aspect_ratio.num;
        sh->codec->par_h = st->sample_aspect_ratio.den;

        uint8_t *sd = av_stream_get_side_data(st, AV_PKT_DATA_DISPLAYMATRIX, NULL);
        if (sd) {
            double r = av_display_rotation_get((uint32_t *)sd);
            if (!isnan(r))
                sh->codec->rotate = (((int)(-r) % 360) + 360) % 360;
        }

        sd = av_stream_get_side_data(st, AV_PKT_DATA_SPHERICAL, NULL);
        if (sd) {
            AVSphericalMapping *sp = (void *)sd;
            struct mp_spherical_params *mpsp = &sh->codec->spherical;
            mpsp->type = sp->projection == AV_SPHERICAL_EQUIRECTANGULAR ?
                            MP_SPHERICAL_EQUIRECTANGULAR : MP_SPHERICAL_UNKNOWN;
            mpsp->ref_angles[0] = sp->yaw / (float)(1 << 16);
            mpsp->ref_angles[1] = sp->pitch / (float)(1 << 16);
            mpsp->ref_angles[2] = sp->roll / (float)(1 << 16);
        }

        // This also applies to vfw-muxed mkv, but we can't detect these easily.
        sh->codec->avi_dts = matches_avinputformat_name(priv, "avi");

        break;
    }
    case AVMEDIA_TYPE_SUBTITLE: {
        sh = demux_alloc_sh_stream(STREAM_SUB);

        if (codec->extradata_size) {
            sh->codec->extradata = talloc_size(sh, codec->extradata_size);
            memcpy(sh->codec->extradata, codec->extradata, codec->extradata_size);
            sh->codec->extradata_size = codec->extradata_size;
        }

        if (matches_avinputformat_name(priv, "microdvd")) {
            AVRational r;
            if (av_opt_get_q(avfc, "subfps", AV_OPT_SEARCH_CHILDREN, &r) >= 0) {
                // File headers don't have a FPS set.
                if (r.num < 1 || r.den < 1)
                    sh->codec->frame_based = 23.976; // default timebase
            }
        }
        break;
    }
    case AVMEDIA_TYPE_ATTACHMENT: {
        AVDictionaryEntry *ftag = av_dict_get(st->metadata, "filename", NULL, 0);
        char *filename = ftag ? ftag->value : NULL;
        AVDictionaryEntry *mt = av_dict_get(st->metadata, "mimetype", NULL, 0);
        char *mimetype = mt ? mt->value : NULL;
        if (mimetype) {
            demuxer_add_attachment(demuxer, filename, mimetype,
                                   codec->extradata, codec->extradata_size);
        }
        break;
    }
    default: ;
    }

    assert(priv->num_streams == i); // directly mapped
    MP_TARRAY_APPEND(priv, priv->streams, priv->num_streams, sh);

    if (sh) {
        sh->ff_index = st->index;
        sh->codec->codec = mp_codec_from_av_codec_id(codec->codec_id);
        sh->codec->codec_tag = codec->codec_tag;
        sh->codec->lav_codecpar = avcodec_parameters_alloc();
        if (sh->codec->lav_codecpar)
            avcodec_parameters_copy(sh->codec->lav_codecpar, codec);
        sh->codec->native_tb_num = st->time_base.num;
        sh->codec->native_tb_den = st->time_base.den;

        if (st->disposition & AV_DISPOSITION_DEFAULT)
            sh->default_track = true;
        if (st->disposition & AV_DISPOSITION_FORCED)
            sh->forced_track = true;
        if (st->disposition & AV_DISPOSITION_DEPENDENT)
            sh->dependent_track = true;
        if (st->disposition & AV_DISPOSITION_VISUAL_IMPAIRED)
            sh->visual_impaired_track = true;
        if (st->disposition & AV_DISPOSITION_HEARING_IMPAIRED)
            sh->hearing_impaired_track = true;
        if (st->disposition & AV_DISPOSITION_STILL_IMAGE)
            sh->still_image = true;
        if (priv->format_hack.use_stream_ids)
            sh->demuxer_id = st->id;
        AVDictionaryEntry *title = av_dict_get(st->metadata, "title", NULL, 0);
        if (title && title->value)
            sh->title = talloc_strdup(sh, title->value);
        if (!sh->title && st->disposition & AV_DISPOSITION_VISUAL_IMPAIRED)
            sh->title = talloc_asprintf(sh, "visual impaired");
        if (!sh->title && st->disposition & AV_DISPOSITION_HEARING_IMPAIRED)
            sh->title = talloc_asprintf(sh, "hearing impaired");
        AVDictionaryEntry *lang = av_dict_get(st->metadata, "language", NULL, 0);
        if (lang && lang->value && strcmp(lang->value, "und") != 0)
            sh->lang = talloc_strdup(sh, lang->value);
        sh->hls_bitrate = dict_get_decimal(st->metadata, "variant_bitrate", 0);
        if (!sh->title && sh->hls_bitrate > 0)
            sh->title = talloc_asprintf(sh, "bitrate %d", sh->hls_bitrate);
        sh->missing_timestamps = !!(priv->avif_flags & AVFMT_NOTIMESTAMPS);
        mp_tags_copy_from_av_dictionary(sh->tags, st->metadata);
        demux_add_sh_stream(demuxer, sh);
    }

    select_tracks(demuxer, i);
}
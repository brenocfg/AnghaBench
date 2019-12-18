#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
typedef  int uint32_t ;
struct sh_stream {struct mp_codec_params* codec; } ;
struct mp_image_params {int w; int h; int /*<<< orphan*/  p_h; int /*<<< orphan*/  p_w; } ;
struct mp_codec_params {int bits_per_coded_sample; int codec_tag; int avi_dts; char* codec; unsigned int extradata_size; int disp_w; int disp_h; int /*<<< orphan*/  color; int /*<<< orphan*/  stereo_mode; int /*<<< orphan*/  par_h; int /*<<< orphan*/  par_w; int /*<<< orphan*/  fps; int /*<<< orphan*/  extradata; } ;
struct TYPE_4__ {char const* codec_id; unsigned char* private_data; int private_size; int v_width; int v_height; int parse; int parse_timebase; int colorspace; int require_keyframes; int v_dwidth; int v_dheight; int /*<<< orphan*/  color; int /*<<< orphan*/  stereo_mode; scalar_t__ v_dheight_set; scalar_t__ v_dwidth_set; int /*<<< orphan*/  v_frate; int /*<<< orphan*/  tnum; } ;
typedef  TYPE_1__ mkv_track_t ;
typedef  int /*<<< orphan*/  demuxer_t ;

/* Variables and functions */
 int AV_RB32 (unsigned char*) ; 
 int AV_RL16 (unsigned char*) ; 
 void* AV_RL32 (unsigned char*) ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  MP_WARN (int /*<<< orphan*/ *,char*,...) ; 
 int RVPROPERTIES_SIZE ; 
 int /*<<< orphan*/  STREAM_VIDEO ; 
 int /*<<< orphan*/  demux_add_sh_stream (int /*<<< orphan*/ *,struct sh_stream*) ; 
 struct sh_stream* demux_alloc_sh_stream (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_track (int /*<<< orphan*/ *,TYPE_1__*,struct sh_stream*) ; 
 char const*** mkv_video_tags ; 
 int /*<<< orphan*/  mp_image_params_set_dsize (struct mp_image_params*,int,int) ; 
 int /*<<< orphan*/  mp_set_codec_from_tag (struct mp_codec_params*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  talloc_memdup (struct mp_codec_params*,unsigned char*,unsigned int) ; 

__attribute__((used)) static int demux_mkv_open_video(demuxer_t *demuxer, mkv_track_t *track)
{
    unsigned char *extradata = NULL;
    unsigned int extradata_size = 0;
    struct sh_stream *sh = demux_alloc_sh_stream(STREAM_VIDEO);
    init_track(demuxer, track, sh);
    struct mp_codec_params *sh_v = sh->codec;

    sh_v->bits_per_coded_sample = 24;

    if (!strcmp(track->codec_id, "V_MS/VFW/FOURCC")) { /* AVI compatibility mode */
        // The private_data contains a BITMAPINFOHEADER struct
        if (track->private_data == NULL || track->private_size < 40)
            goto done;

        unsigned char *h = track->private_data;
        if (track->v_width == 0)
            track->v_width = AV_RL32(h + 4);        // biWidth
        if (track->v_height == 0)
            track->v_height = AV_RL32(h + 8);       // biHeight
        sh_v->bits_per_coded_sample = AV_RL16(h + 14); // biBitCount
        sh_v->codec_tag = AV_RL32(h + 16);            // biCompression

        extradata = track->private_data + 40;
        extradata_size = track->private_size - 40;
        mp_set_codec_from_tag(sh_v);
        sh_v->avi_dts = true;
    } else if (track->private_size >= RVPROPERTIES_SIZE
               && (!strcmp(track->codec_id, "V_REAL/RV10")
                || !strcmp(track->codec_id, "V_REAL/RV20")
                || !strcmp(track->codec_id, "V_REAL/RV30")
                || !strcmp(track->codec_id, "V_REAL/RV40")))
    {
        unsigned char *src;
        unsigned int cnt;

        src = (uint8_t *) track->private_data + RVPROPERTIES_SIZE;

        cnt = track->private_size - RVPROPERTIES_SIZE;
        uint32_t t2 = AV_RB32(src - 4);
        switch (t2 == 0x10003000 || t2 == 0x10003001 ? '1' : track->codec_id[9]) {
        case '1': sh_v->codec = "rv10"; break;
        case '2': sh_v->codec = "rv20"; break;
        case '3': sh_v->codec = "rv30"; break;
        case '4': sh_v->codec = "rv40"; break;
        }
        // copy type1 and type2 info from rv properties
        extradata_size = cnt + 8;
        extradata = src - 8;
        track->parse = true;
        track->parse_timebase = 1e3;
    } else if (strcmp(track->codec_id, "V_UNCOMPRESSED") == 0) {
        // raw video, "like AVI" - this is a FourCC
        sh_v->codec_tag = track->colorspace;
        sh_v->codec = "rawvideo";
    } else if (strcmp(track->codec_id, "V_QUICKTIME") == 0) {
        uint32_t fourcc1 = 0, fourcc2 = 0;
        if (track->private_size >= 8) {
            fourcc1 = AV_RL32(track->private_data + 0);
            fourcc2 = AV_RL32(track->private_data + 4);
        }
        if (fourcc1 == MKTAG('S', 'V', 'Q', '3') ||
            fourcc2 == MKTAG('S', 'V', 'Q', '3'))
        {
            sh_v->codec = "svq3";
            extradata = track->private_data;
            extradata_size = track->private_size;
        }
    } else {
        for (int i = 0; mkv_video_tags[i][0]; i++) {
            if (!strcmp(mkv_video_tags[i][0], track->codec_id)) {
                sh_v->codec = mkv_video_tags[i][1];
                break;
            }
        }
        if (track->private_data && track->private_size > 0) {
            extradata = track->private_data;
            extradata_size = track->private_size;
        }
    }

    const char *codec = sh_v->codec ? sh_v->codec : "";
    if (!strcmp(codec, "mjpeg")) {
        sh_v->codec_tag = MKTAG('m', 'j', 'p', 'g');
        track->require_keyframes = true;
    }

    if (extradata_size > 0x1000000) {
        MP_WARN(demuxer, "Invalid CodecPrivate\n");
        goto done;
    }

    sh_v->extradata = talloc_memdup(sh_v, extradata, extradata_size);
    sh_v->extradata_size = extradata_size;
    if (!sh_v->codec) {
        MP_WARN(demuxer, "Unknown/unsupported CodecID (%s) or missing/bad "
                "CodecPrivate data (track %d).\n",
                track->codec_id, track->tnum);
    }
    sh_v->fps = track->v_frate;
    sh_v->disp_w = track->v_width;
    sh_v->disp_h = track->v_height;

    int dw = track->v_dwidth_set ? track->v_dwidth : track->v_width;
    int dh = track->v_dheight_set ? track->v_dheight : track->v_height;
    struct mp_image_params p = {.w = track->v_width, .h = track->v_height};
    mp_image_params_set_dsize(&p, dw, dh);
    sh_v->par_w = p.p_w;
    sh_v->par_h = p.p_h;

    sh_v->stereo_mode = track->stereo_mode;
    sh_v->color = track->color;

done:
    demux_add_sh_stream(demuxer, sh);

    return 0;
}
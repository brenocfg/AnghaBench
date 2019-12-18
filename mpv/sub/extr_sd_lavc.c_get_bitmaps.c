#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sub_bitmaps {int num_parts; struct sub_bitmap* parts; int /*<<< orphan*/  format; int /*<<< orphan*/  packed_h; int /*<<< orphan*/  packed_w; int /*<<< orphan*/  packed; int /*<<< orphan*/  change_id; } ;
struct sub_bitmap {int y; float x; float dw; float dh; } ;
struct sub {int count; scalar_t__ id; int src_w; int src_h; int /*<<< orphan*/  bound_h; int /*<<< orphan*/  bound_w; int /*<<< orphan*/  data; struct sub_bitmap* inbitmaps; } ;
struct TYPE_4__ {double p_w; int w; int h; scalar_t__ p_h; } ;
struct sd_lavc_priv {double current_pts; scalar_t__ displayed_id; TYPE_2__ video_params; TYPE_1__* avctx; struct sub_bitmap* outbitmaps; } ;
struct sd {struct mp_subtitle_opts* opts; struct sd_lavc_priv* priv; } ;
struct mp_subtitle_opts {int sub_pos; double sub_scale; scalar_t__ ass_style_override; scalar_t__ image_subs_video_res; scalar_t__ stretch_image_subs; scalar_t__ stretch_dvd_subs; } ;
struct mp_osd_res {scalar_t__ mb; scalar_t__ mt; scalar_t__ mr; scalar_t__ ml; } ;
struct TYPE_3__ {scalar_t__ codec_id; int width; int height; } ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_DVD_SUBTITLE ; 
 scalar_t__ AV_CODEC_ID_HDMV_PGS_SUBTITLE ; 
 int MPMAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_TARRAY_GROW (struct sd_lavc_priv*,struct sub_bitmap*,int) ; 
 int /*<<< orphan*/  SUBBITMAP_RGBA ; 
 struct sub* get_current (struct sd_lavc_priv*,double) ; 
 scalar_t__ isnormal (double) ; 
 int /*<<< orphan*/  osd_rescale_bitmaps (struct sub_bitmaps*,int,int,struct mp_osd_res,double) ; 

__attribute__((used)) static void get_bitmaps(struct sd *sd, struct mp_osd_res d, int format,
                        double pts, struct sub_bitmaps *res)
{
    struct sd_lavc_priv *priv = sd->priv;
    struct mp_subtitle_opts *opts = sd->opts;

    priv->current_pts = pts;

    struct sub *current = get_current(priv, pts);

    if (!current)
        return;

    MP_TARRAY_GROW(priv, priv->outbitmaps, current->count);
    for (int n = 0; n < current->count; n++)
        priv->outbitmaps[n] = current->inbitmaps[n];

    res->parts = priv->outbitmaps;
    res->num_parts = current->count;
    if (priv->displayed_id != current->id)
        res->change_id++;
    priv->displayed_id = current->id;
    res->packed = current->data;
    res->packed_w = current->bound_w;
    res->packed_h = current->bound_h;
    res->format = SUBBITMAP_RGBA;

    double video_par = 0;
    if (priv->avctx->codec_id == AV_CODEC_ID_DVD_SUBTITLE &&
        opts->stretch_dvd_subs)
    {
        // For DVD subs, try to keep the subtitle PAR at display PAR.
        double par = priv->video_params.p_w / (double)priv->video_params.p_h;
        if (isnormal(par))
            video_par = par;
    }
    if (priv->avctx->codec_id == AV_CODEC_ID_HDMV_PGS_SUBTITLE)
        video_par = -1;
    if (opts->stretch_image_subs)
        d.ml = d.mr = d.mt = d.mb = 0;
    int w = priv->avctx->width;
    int h = priv->avctx->height;
    if (w <= 0 || h <= 0 || opts->image_subs_video_res) {
        w = priv->video_params.w;
        h = priv->video_params.h;
    }
    if (current->src_w > w || current->src_h > h) {
        w = priv->video_params.w;
        h = priv->video_params.h;
    }

    if (opts->sub_pos != 100 && opts->ass_style_override) {
        int offset = (100 - opts->sub_pos) / 100.0 * h;

        for (int n = 0; n < res->num_parts; n++) {
            struct sub_bitmap *sub = &res->parts[n];

            // Decide by heuristic whether this is a sub-title or something
            // else (top-title, covering whole screen).
            if (sub->y < h / 2)
                continue;

            // Allow moving up the subtitle, but only until it clips.
            sub->y = MPMAX(sub->y - offset, 0);
        }
    }

    osd_rescale_bitmaps(res, w, h, d, video_par);

    if (opts->sub_scale != 1.0 && opts->ass_style_override) {
        for (int n = 0; n < res->num_parts; n++) {
            struct sub_bitmap *sub = &res->parts[n];

            float shit = (opts->sub_scale - 1.0f) / 2;

            // Fortunately VO isn't supposed to give a FUCKING FUCK about
            // whether the sub might e.g. go outside of the screen.
            sub->x -= sub->dw * shit;
            sub->y -= sub->dh * shit;
            sub->dw += sub->dw * shit * 2;
            sub->dh += sub->dh * shit * 2;
        }
    }

}
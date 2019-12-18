#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {double start_display_time; double end_display_time; int num_rects; TYPE_1__** rects; } ;
struct lavc_conv {char** cur_list; TYPE_7__ cur; int /*<<< orphan*/  codec; TYPE_3__* avctx; } ;
struct demux_packet {double pts; } ;
struct TYPE_14__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_13__ {scalar_t__ pts; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {scalar_t__ w; scalar_t__ h; char* ass; } ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct lavc_conv*,char*) ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct lavc_conv*,char**,int,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct lavc_conv*,char*) ; 
 double UINT32_MAX ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int avcodec_decode_subtitle2 (TYPE_3__*,TYPE_7__*,int*,TYPE_2__*) ; 
 int /*<<< orphan*/  avsubtitle_free (TYPE_7__*) ; 
 double mp_pts_from_av (double,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_set_av_packet (TYPE_2__*,struct demux_packet*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_webvtt (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

char **lavc_conv_decode(struct lavc_conv *priv, struct demux_packet *packet,
                        double *sub_pts, double *sub_duration)
{
    AVCodecContext *avctx = priv->avctx;
    AVPacket pkt;
    AVPacket parsed_pkt = {0};
    int ret, got_sub;
    int num_cur = 0;

    avsubtitle_free(&priv->cur);

    mp_set_av_packet(&pkt, packet, &avctx->time_base);
    if (pkt.pts < 0)
        pkt.pts = 0;

    if (strcmp(priv->codec, "webvtt-webm") == 0) {
        if (parse_webvtt(&pkt, &parsed_pkt) < 0) {
            MP_ERR(priv, "Error parsing subtitle\n");
            goto done;
        }
        pkt = parsed_pkt;
    }

    ret = avcodec_decode_subtitle2(avctx, &priv->cur, &got_sub, &pkt);
    if (ret < 0) {
        MP_ERR(priv, "Error decoding subtitle\n");
    } else if (got_sub) {
        *sub_pts = packet->pts + mp_pts_from_av(priv->cur.start_display_time,
                                               &avctx->time_base);
        *sub_duration = priv->cur.end_display_time == UINT32_MAX ?
                        UINT32_MAX :
                        mp_pts_from_av(priv->cur.end_display_time -
                                       priv->cur.start_display_time,
                                       &avctx->time_base);

        for (int i = 0; i < priv->cur.num_rects; i++) {
            if (priv->cur.rects[i]->w > 0 && priv->cur.rects[i]->h > 0)
                MP_WARN(priv, "Ignoring bitmap subtitle.\n");
            char *ass_line = priv->cur.rects[i]->ass;
            if (!ass_line)
                continue;
            MP_TARRAY_APPEND(priv, priv->cur_list, num_cur, ass_line);
        }
    }

done:
    av_packet_unref(&parsed_pkt);
    MP_TARRAY_APPEND(priv, priv->cur_list, num_cur, NULL);
    return priv->cur_list;
}
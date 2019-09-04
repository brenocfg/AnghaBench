#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct demux_packet {int duration; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; TYPE_1__* avpacket; scalar_t__ keyframe; int /*<<< orphan*/  len; int /*<<< orphan*/ * buffer; } ;
struct TYPE_11__ {int duration; void* dts; void* pts; int /*<<< orphan*/  flags; int /*<<< orphan*/  buf; int /*<<< orphan*/ * data; int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  side_data; int /*<<< orphan*/  size; } ;
struct TYPE_10__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  buf; int /*<<< orphan*/ * data; int /*<<< orphan*/  side_data_elems; int /*<<< orphan*/  side_data; } ;
typedef  TYPE_2__ AVRational ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_init_packet (TYPE_3__*) ; 
 int av_q2d (TYPE_2__) ; 
 void* mp_pts_to_av (int /*<<< orphan*/ ,TYPE_2__*) ; 

void mp_set_av_packet(AVPacket *dst, struct demux_packet *mpkt, AVRational *tb)
{
    av_init_packet(dst);
    dst->data = mpkt ? mpkt->buffer : NULL;
    dst->size = mpkt ? mpkt->len : 0;
    /* Some codecs (ZeroCodec, some cases of PNG) may want keyframe info
     * from demuxer. */
    if (mpkt && mpkt->keyframe)
        dst->flags |= AV_PKT_FLAG_KEY;
    if (mpkt && mpkt->avpacket) {
        dst->side_data = mpkt->avpacket->side_data;
        dst->side_data_elems = mpkt->avpacket->side_data_elems;
        if (dst->data == mpkt->avpacket->data)
            dst->buf = mpkt->avpacket->buf;
        dst->flags |= mpkt->avpacket->flags;
    }
    if (mpkt && tb && tb->num > 0 && tb->den > 0)
        dst->duration = mpkt->duration / av_q2d(*tb);
    dst->pts = mp_pts_to_av(mpkt ? mpkt->pts : MP_NOPTS_VALUE, tb);
    dst->dts = mp_pts_to_av(mpkt ? mpkt->dts : MP_NOPTS_VALUE, tb);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mp_image {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_PNG ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_new_packet (TYPE_1__*,size_t) ; 
 TYPE_1__* av_packet_alloc () ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 int /*<<< orphan*/ * avcodec_alloc_context3 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ **) ; 
 scalar_t__ avcodec_open2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ avcodec_receive_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_send_packet (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct mp_image* convert_image (struct mp_image*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 struct mp_image* mp_image_from_av_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_null_log ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

struct mp_image *load_image_png_buf(void *buffer, size_t buffer_size, int imgfmt)
{
    const AVCodec *codec = avcodec_find_decoder(AV_CODEC_ID_PNG);
    if (!codec)
        return NULL;

    AVCodecContext *avctx = avcodec_alloc_context3(codec);
    if (!avctx)
        return NULL;

    if (avcodec_open2(avctx, codec, NULL) < 0) {
        avcodec_free_context(&avctx);
        return NULL;
    }

    AVPacket *pkt = av_packet_alloc();
    if (pkt) {
        if (av_new_packet(pkt, buffer_size) >= 0)
            memcpy(pkt->data, buffer, buffer_size);
    }

    // (There is only 1 outcome: either it takes it and decodes it, or not.)
    avcodec_send_packet(avctx, pkt);
    avcodec_send_packet(avctx, NULL);

    av_packet_free(&pkt);

    struct mp_image *res = NULL;
    AVFrame *frame = av_frame_alloc();
    if (frame && avcodec_receive_frame(avctx, frame) >= 0) {
        struct mp_image *r = mp_image_from_av_frame(frame);
        if (r)
            res = convert_image(r, imgfmt, NULL, mp_null_log);
        talloc_free(r);
    }
    av_frame_free(&frame);

    avcodec_free_context(&avctx);
    return res;
}
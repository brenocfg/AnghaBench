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
struct mp_codec_params {int dummy; } ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_4__ {int codec_type; int codec_id; } ;
typedef  int /*<<< orphan*/  AVCodecParameters ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVMEDIA_TYPE_UNKNOWN ; 
 int AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  avcodec_parameters_free (int /*<<< orphan*/ **) ; 
 scalar_t__ avcodec_parameters_to_context (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mp_codec_params_to_av (struct mp_codec_params*) ; 

int mp_set_avctx_codec_headers(AVCodecContext *avctx, struct mp_codec_params *c)
{
    enum AVMediaType codec_type = avctx->codec_type;
    enum AVCodecID codec_id = avctx->codec_id;
    AVCodecParameters *avp = mp_codec_params_to_av(c);
    if (!avp)
        return -1;

    int r = avcodec_parameters_to_context(avctx, avp) < 0 ? -1 : 0;
    avcodec_parameters_free(&avp);

    if (avctx->codec_type != AVMEDIA_TYPE_UNKNOWN)
        avctx->codec_type = codec_type;
    if (avctx->codec_id != AV_CODEC_ID_NONE)
        avctx->codec_id = codec_id;
    return r;
}
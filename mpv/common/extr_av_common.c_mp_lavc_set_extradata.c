#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 

int mp_lavc_set_extradata(AVCodecContext *avctx, void *ptr, int size)
{
    if (size) {
        av_free(avctx->extradata);
        avctx->extradata_size = 0;
        avctx->extradata = av_mallocz(size + AV_INPUT_BUFFER_PADDING_SIZE);
        if (!avctx->extradata)
            return -1;
        avctx->extradata_size = size;
        memcpy(avctx->extradata, ptr, size);
    }
    return 0;
}
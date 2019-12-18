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
struct TYPE_3__ {int id; } ;
struct image_writer_ctx {TYPE_2__* opts; TYPE_1__ original_format; } ;
struct AVCodec {int dummy; } ;
struct TYPE_4__ {int high_bit_depth; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int IMGFMT_RGB0 ; 
 struct AVCodec* avcodec_find_encoder (int /*<<< orphan*/ ) ; 
 int get_encoder_format (struct AVCodec*,int,int) ; 

__attribute__((used)) static int get_target_format(struct image_writer_ctx *ctx)
{
    struct AVCodec *codec = avcodec_find_encoder(ctx->opts->format);
    if (!codec)
        goto unknown;

    int srcfmt = ctx->original_format.id;

    int target = get_encoder_format(codec, srcfmt, ctx->opts->high_bit_depth);
    if (!target)
        target = get_encoder_format(codec, srcfmt, true);

    if (!target)
        goto unknown;

    return target;

unknown:
    return IMGFMT_RGB0;
}
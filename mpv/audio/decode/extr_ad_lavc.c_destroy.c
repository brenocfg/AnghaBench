#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct priv {int /*<<< orphan*/  avframe; int /*<<< orphan*/  avctx; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_free_context (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy(struct mp_filter *da)
{
    struct priv *ctx = da->priv;

    avcodec_free_context(&ctx->avctx);
    av_frame_free(&ctx->avframe);
}
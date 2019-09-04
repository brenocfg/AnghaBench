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
struct priv {int preroll_done; int eof_returned; int /*<<< orphan*/  next_pts; scalar_t__ trim_samples; scalar_t__ skip_samples; int /*<<< orphan*/  avctx; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset(struct mp_filter *da)
{
    struct priv *ctx = da->priv;

    avcodec_flush_buffers(ctx->avctx);
    ctx->skip_samples = 0;
    ctx->trim_samples = 0;
    ctx->preroll_done = false;
    ctx->next_pts = MP_NOPTS_VALUE;
    ctx->eof_returned = false;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int eof_returned; scalar_t__ framedrop_flags; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_all (struct mp_filter*) ; 

__attribute__((used)) static void reset(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    flush_all(vd);

    ctx->eof_returned = false;
    ctx->framedrop_flags = 0;
}
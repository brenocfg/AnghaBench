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
struct priv {int /*<<< orphan*/  pool_fmt; int /*<<< orphan*/  avrctx_fmt; int /*<<< orphan*/  pre_out_fmt; scalar_t__ avrctx_out; scalar_t__ avrctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avresample_close (scalar_t__) ; 
 int /*<<< orphan*/  avresample_free (scalar_t__*) ; 

__attribute__((used)) static void close_lavrr(struct priv *p)
{
    if (p->avrctx)
        avresample_close(p->avrctx);
    avresample_free(&p->avrctx);
    if (p->avrctx_out)
        avresample_close(p->avrctx_out);
    avresample_free(&p->avrctx_out);

    TA_FREEP(&p->pre_out_fmt);
    TA_FREEP(&p->avrctx_fmt);
    TA_FREEP(&p->pool_fmt);
}
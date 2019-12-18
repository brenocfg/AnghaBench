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
struct priv {int /*<<< orphan*/  avrctx; int /*<<< orphan*/  input; int /*<<< orphan*/  current_pts; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 scalar_t__ avresample_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_lavrr (struct priv*) ; 
 int /*<<< orphan*/  swr_close (int /*<<< orphan*/ ) ; 
 scalar_t__ swr_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset(struct mp_filter *f)
{
    struct priv *p = f->priv;

    p->current_pts = MP_NOPTS_VALUE;
    TA_FREEP(&p->input);

    if (!p->avrctx)
        return;
#if HAVE_LIBSWRESAMPLE
    swr_close(p->avrctx);
    if (swr_init(p->avrctx) < 0)
        close_lavrr(p);
#else
    while (avresample_read(p->avrctx, NULL, 1000) > 0) {}
#endif
}
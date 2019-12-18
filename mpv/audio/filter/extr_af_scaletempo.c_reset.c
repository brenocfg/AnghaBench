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
struct priv {int /*<<< orphan*/  in; int /*<<< orphan*/  bytes_overlap; int /*<<< orphan*/  buf_overlap; scalar_t__ frames_stride_error; scalar_t__ bytes_to_slide; scalar_t__ bytes_queued; int /*<<< orphan*/  current_pts; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_NOPTS_VALUE ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset(struct mp_filter *f)
{
    struct priv *s = f->priv;

    s->current_pts = MP_NOPTS_VALUE;
    s->bytes_queued = 0;
    s->bytes_to_slide = 0;
    s->frames_stride_error = 0;
    memset(s->buf_overlap, 0, s->bytes_overlap);
    TA_FREEP(&s->in);
}
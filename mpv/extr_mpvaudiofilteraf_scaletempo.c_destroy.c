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
struct priv {int /*<<< orphan*/  in; int /*<<< orphan*/  table_window; int /*<<< orphan*/  table_blend; int /*<<< orphan*/  buf_pre_corr; int /*<<< orphan*/  buf_overlap; int /*<<< orphan*/  buf_queue; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_filter_free_children (struct mp_filter*) ; 

__attribute__((used)) static void destroy(struct mp_filter *f)
{
    struct priv *s = f->priv;
    free(s->buf_queue);
    free(s->buf_overlap);
    free(s->buf_pre_corr);
    free(s->table_blend);
    free(s->table_window);
    TA_FREEP(&s->in);
    mp_filter_free_children(f);
}
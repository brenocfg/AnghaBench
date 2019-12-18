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
struct priv {int /*<<< orphan*/  decoded_coverart; TYPE_1__* decoder; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_DBG (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  mp_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy(struct mp_filter *f)
{
    struct priv *p = f->priv;
    if (p->decoder) {
        MP_DBG(f, "Uninit decoder.\n");
        talloc_free(p->decoder->f);
        p->decoder = NULL;
    }
    reset(f);
    mp_frame_unref(&p->decoded_coverart);
}
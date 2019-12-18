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
struct priv {int sent_final; int /*<<< orphan*/  pending; scalar_t__ rubber_delay; scalar_t__ rubber; } ;
struct mp_filter {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rubberband_reset (scalar_t__) ; 

__attribute__((used)) static void reset(struct mp_filter *f)
{
    struct priv *p = f->priv;

    if (p->rubber)
        rubberband_reset(p->rubber);
    p->rubber_delay = 0;
    p->sent_final = false;
    TA_FREEP(&p->pending);
}
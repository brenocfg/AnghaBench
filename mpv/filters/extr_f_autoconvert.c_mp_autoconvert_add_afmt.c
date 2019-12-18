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
struct priv {int force_update; int /*<<< orphan*/  num_afmts; int /*<<< orphan*/  afmts; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mp_autoconvert_add_afmt(struct mp_autoconvert *c, int afmt)
{
    struct priv *p = c->f->priv;

    MP_TARRAY_APPEND(p, p->afmts, p->num_afmts, afmt);
    p->force_update = true;
}
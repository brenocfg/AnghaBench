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
struct priv {int force_update; int /*<<< orphan*/  chmaps; } ;
struct mp_chmap {int dummy; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_chmap_sel_add_map (int /*<<< orphan*/ *,struct mp_chmap*) ; 

void mp_autoconvert_add_chmap(struct mp_autoconvert *c, struct mp_chmap *chmap)
{
    struct priv *p = c->f->priv;

    mp_chmap_sel_add_map(&p->chmaps, chmap);
    p->force_update = true;
}
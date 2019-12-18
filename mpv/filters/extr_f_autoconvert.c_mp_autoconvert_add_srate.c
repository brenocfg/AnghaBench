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
struct priv {size_t num_srates; int force_update; scalar_t__* srates; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct priv*,scalar_t__*,size_t,int) ; 
 int /*<<< orphan*/  MP_TARRAY_GROW (struct priv*,scalar_t__*,size_t) ; 

void mp_autoconvert_add_srate(struct mp_autoconvert *c, int rate)
{
    struct priv *p = c->f->priv;

    MP_TARRAY_APPEND(p, p->srates, p->num_srates, rate);
    // Some other API we call expects a 0-terminated sample rates array.
    MP_TARRAY_GROW(p, p->srates, p->num_srates);
    p->srates[p->num_srates] = 0;
    p->force_update = true;
}
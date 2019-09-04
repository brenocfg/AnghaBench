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
struct priv {int* imgfmts; size_t num_imgfmts; int* subfmts; int force_update; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_GROW (struct priv*,int*,size_t) ; 

void mp_autoconvert_add_imgfmt(struct mp_autoconvert *c, int imgfmt, int subfmt)
{
    struct priv *p = c->f->priv;

    MP_TARRAY_GROW(p, p->imgfmts, p->num_imgfmts);
    MP_TARRAY_GROW(p, p->subfmts, p->num_imgfmts);

    p->imgfmts[p->num_imgfmts] = imgfmt;
    p->subfmts[p->num_imgfmts] = subfmt;

    p->num_imgfmts += 1;
    p->force_update = true;
}
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
struct mp_image_params {scalar_t__ imgfmt; scalar_t__ hw_subfmt; } ;
struct priv {int imgparams_set; int num_imgfmts; scalar_t__* imgfmts; scalar_t__* subfmts; struct mp_image_params imgparams; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_autoconvert_add_imgfmt (struct mp_autoconvert*,scalar_t__,scalar_t__) ; 
 scalar_t__ mp_image_params_equal (struct mp_image_params*,struct mp_image_params*) ; 

void mp_autoconvert_set_target_image_params(struct mp_autoconvert *c,
                                            struct mp_image_params *par)
{
    struct priv *p = c->f->priv;

    if (p->imgparams_set && mp_image_params_equal(&p->imgparams, par) &&
        p->num_imgfmts == 1 && p->imgfmts[0] == par->imgfmt &&
        p->subfmts[0] == par->hw_subfmt)
        return;

    p->imgparams = *par;
    p->imgparams_set = true;

    p->num_imgfmts = 0;
    mp_autoconvert_add_imgfmt(c, par->imgfmt, par->hw_subfmt);
}
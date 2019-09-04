#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_2__* decoder; } ;
struct mp_decoder_wrapper {TYPE_1__* f; } ;
typedef  enum dec_ctrl { ____Placeholder_dec_ctrl } dec_ctrl ;
struct TYPE_4__ {int (* control ) (int /*<<< orphan*/ ,int,void*) ;int /*<<< orphan*/  f; } ;
struct TYPE_3__ {struct priv* priv; } ;

/* Variables and functions */
 int CONTROL_UNKNOWN ; 
 int stub1 (int /*<<< orphan*/ ,int,void*) ; 

int mp_decoder_wrapper_control(struct mp_decoder_wrapper *d,
                               enum dec_ctrl cmd, void *arg)
{
    struct priv *p = d->f->priv;
    if (p->decoder && p->decoder->control)
        return p->decoder->control(p->decoder->f, cmd, arg);
    return CONTROL_UNKNOWN;
}
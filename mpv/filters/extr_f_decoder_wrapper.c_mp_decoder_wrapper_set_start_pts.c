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
struct priv {double start_pts; } ;
struct mp_decoder_wrapper {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */

void mp_decoder_wrapper_set_start_pts(struct mp_decoder_wrapper *d, double pts)
{
    struct priv *p = d->f->priv;
    p->start_pts = pts;
}
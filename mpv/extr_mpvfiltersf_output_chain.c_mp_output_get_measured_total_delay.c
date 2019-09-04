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
struct mp_user_filter {scalar_t__ last_in_pts; scalar_t__ last_out_pts; } ;
struct mp_output_chain {TYPE_1__* f; } ;
struct chain {int num_all_filters; struct mp_user_filter** all_filters; } ;
struct TYPE_2__ {struct chain* priv; } ;

/* Variables and functions */
 scalar_t__ MP_NOPTS_VALUE ; 

double mp_output_get_measured_total_delay(struct mp_output_chain *c)
{
    struct chain *p = c->f->priv;

    double delay = 0;

    for (int n = 0; n < p->num_all_filters; n++) {
        struct mp_user_filter *u = p->all_filters[n];

        if (u->last_in_pts != MP_NOPTS_VALUE &&
            u->last_out_pts != MP_NOPTS_VALUE)
        {
            delay += u->last_in_pts - u->last_out_pts;
        }
    }

    return delay;
}
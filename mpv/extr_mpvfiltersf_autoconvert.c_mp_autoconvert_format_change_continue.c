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
struct priv {int format_change_blocked; int format_change_cont; } ;
struct mp_autoconvert {TYPE_1__* f; } ;
struct TYPE_2__ {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_filter_wakeup (TYPE_1__*) ; 

void mp_autoconvert_format_change_continue(struct mp_autoconvert *c)
{
    struct priv *p = c->f->priv;

    if (p->format_change_blocked) {
        p->format_change_cont = true;
        p->format_change_blocked = false;
        mp_filter_wakeup(c->f);
    }
}
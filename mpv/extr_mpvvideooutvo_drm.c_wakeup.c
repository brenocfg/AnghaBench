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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  vt_switcher; scalar_t__ vt_switcher_active; } ;

/* Variables and functions */
 int /*<<< orphan*/  vt_switcher_interrupt_poll (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wakeup(struct vo *vo)
{
    struct priv *p = vo->priv;
    if (p->vt_switcher_active)
        vt_switcher_interrupt_poll(&p->vt_switcher);
}
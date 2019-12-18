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
struct TYPE_2__ {scalar_t__ rate; } ;
struct priv {double delay; TYPE_1__ par; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  update (struct ao*) ; 

__attribute__((used)) static double get_delay(struct ao *ao)
{
    struct priv *p = ao->priv;

    update(ao);

    return p->delay / (double)p->par.rate;
}
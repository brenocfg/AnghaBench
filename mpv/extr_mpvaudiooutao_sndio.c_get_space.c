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
struct TYPE_2__ {int bufsz; int round; } ;
struct priv {int delay; TYPE_1__ par; } ;
struct ao {struct priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  update (struct ao*) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct priv *p = ao->priv;

    update(ao);

    int samples = p->par.bufsz - p->delay;
    return samples / p->par.round * p->par.round;
}
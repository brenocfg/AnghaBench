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
struct priv {int activated; TYPE_1__* opts; int /*<<< orphan*/  client; } ;
struct ao {struct priv* priv; } ;
struct TYPE_2__ {scalar_t__ connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_FATAL (struct ao*,char*) ; 
 int /*<<< orphan*/  connect_to_outports (struct ao*) ; 
 scalar_t__ jack_activate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resume(struct ao *ao)
{
    struct priv *p = ao->priv;
    if (!p->activated) {
        p->activated = true;

        if (jack_activate(p->client))
            MP_FATAL(ao, "activate failed\n");

        if (p->opts->connect)
            connect_to_outports(ao);
    }
}
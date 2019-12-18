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
struct TYPE_4__ {int ifconfig_pool_persist_owned; int /*<<< orphan*/ * ifconfig_pool_persist; } ;
struct context {TYPE_2__ c1; TYPE_1__* sig; } ;
struct TYPE_3__ {scalar_t__ signal_received; } ;

/* Variables and functions */
 scalar_t__ SIGUSR1 ; 
 int /*<<< orphan*/  ifconfig_pool_persist_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_close_ifconfig_pool_persist(struct context *c)
{
#if P2MP_SERVER
    if (!(c->sig->signal_received == SIGUSR1))
    {
        if (c->c1.ifconfig_pool_persist && c->c1.ifconfig_pool_persist_owned)
        {
            ifconfig_pool_persist_close(c->c1.ifconfig_pool_persist);
            c->c1.ifconfig_pool_persist = NULL;
            c->c1.ifconfig_pool_persist_owned = false;
        }
    }
#endif
}
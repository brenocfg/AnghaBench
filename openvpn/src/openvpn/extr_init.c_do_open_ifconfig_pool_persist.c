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
struct TYPE_4__ {int ifconfig_pool_persist_owned; scalar_t__ ifconfig_pool_persist; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifconfig_pool_persist_refresh_freq; scalar_t__ ifconfig_pool_persist_filename; } ;
struct context {TYPE_2__ c1; TYPE_1__ options; } ;

/* Variables and functions */
 scalar_t__ ifconfig_pool_persist_init (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_open_ifconfig_pool_persist(struct context *c)
{
#if P2MP_SERVER
    if (!c->c1.ifconfig_pool_persist && c->options.ifconfig_pool_persist_filename)
    {
        c->c1.ifconfig_pool_persist = ifconfig_pool_persist_init(c->options.ifconfig_pool_persist_filename,
                                                                 c->options.ifconfig_pool_persist_refresh_freq);
        c->c1.ifconfig_pool_persist_owned = true;
    }
#endif
}
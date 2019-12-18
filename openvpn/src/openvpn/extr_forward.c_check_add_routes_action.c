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
struct TYPE_3__ {int /*<<< orphan*/  route_wakeup_expire; int /*<<< orphan*/  route_wakeup; int /*<<< orphan*/  es; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuntap; int /*<<< orphan*/  route_ipv6_list; int /*<<< orphan*/  route_list; } ;
struct context {TYPE_1__ c2; int /*<<< orphan*/  net_ctx; int /*<<< orphan*/  plugins; TYPE_2__ c1; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_ERRORS ; 
 int /*<<< orphan*/  do_route (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_timeout_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initialization_sequence_completed (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_time () ; 

__attribute__((used)) static void
check_add_routes_action(struct context *c, const bool errors)
{
    do_route(&c->options, c->c1.route_list, c->c1.route_ipv6_list,
             c->c1.tuntap, c->plugins, c->c2.es, &c->net_ctx);
    update_time();
    event_timeout_clear(&c->c2.route_wakeup);
    event_timeout_clear(&c->c2.route_wakeup_expire);
    initialization_sequence_completed(c, errors ? ISC_ERRORS : 0); /* client/p2p --route-delay was defined */
}
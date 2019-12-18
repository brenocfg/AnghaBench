#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int n; } ;
struct TYPE_7__ {int /*<<< orphan*/  ping_rec_interval; TYPE_4__ route_wakeup; int /*<<< orphan*/  timeval; int /*<<< orphan*/  route_wakeup_expire; } ;
struct TYPE_6__ {int restart_sleep_seconds; } ;
struct TYPE_5__ {scalar_t__ tuntap; int /*<<< orphan*/  route_list; } ;
struct context {TYPE_3__ c2; TYPE_2__ persist; TYPE_1__ c1; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ROUTE ; 
 int /*<<< orphan*/  ETT_DEFAULT ; 
 int M_INFO ; 
 int M_NOPREFIX ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  check_add_routes_action (struct context*,int) ; 
 int /*<<< orphan*/  event_timeout_init (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_timeout_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  show_adapters (int) ; 
 int /*<<< orphan*/  show_routes (int) ; 
 scalar_t__ test_routes (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tun_standby (scalar_t__) ; 
 int /*<<< orphan*/  update_time () ; 

void
check_add_routes_dowork(struct context *c)
{
    if (test_routes(c->c1.route_list, c->c1.tuntap))
    {
        check_add_routes_action(c, false);
    }
    else if (event_timeout_trigger(&c->c2.route_wakeup_expire, &c->c2.timeval, ETT_DEFAULT))
    {
        check_add_routes_action(c, true);
    }
    else
    {
        msg(D_ROUTE, "Route: Waiting for TUN/TAP interface to come up...");
        if (c->c1.tuntap)
        {
            if (!tun_standby(c->c1.tuntap))
            {
                register_signal(c, SIGHUP, "ip-fail");
                c->persist.restart_sleep_seconds = 10;
#ifdef _WIN32
                show_routes(M_INFO|M_NOPREFIX);
                show_adapters(M_INFO|M_NOPREFIX);
#endif
            }
        }
        update_time();
        if (c->c2.route_wakeup.n != 1)
        {
            event_timeout_init(&c->c2.route_wakeup, 1, now);
        }
        event_timeout_reset(&c->c2.ping_rec_interval);
    }
}
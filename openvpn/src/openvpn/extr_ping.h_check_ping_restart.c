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
struct TYPE_7__ {int /*<<< orphan*/  actual; } ;
struct TYPE_8__ {TYPE_3__ link_socket_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  ping_timer_remote; scalar_t__ ping_rec_timeout; } ;
struct TYPE_5__ {int /*<<< orphan*/  timeval; int /*<<< orphan*/  ping_rec_interval; } ;
struct context {TYPE_4__ c1; TYPE_2__ options; TYPE_1__ c2; } ;

/* Variables and functions */
 int ETT_DEFAULT ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ link_socket_actual_defined (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
check_ping_restart(struct context *c)
{
    void check_ping_restart_dowork(struct context *c);

    if (c->options.ping_rec_timeout
        && event_timeout_trigger(&c->c2.ping_rec_interval,
                                 &c->c2.timeval,
                                 (!c->options.ping_timer_remote
                                  || link_socket_actual_defined(&c->c1.link_socket_addr.actual))
                                 ? ETT_DEFAULT : 15))
    {
        check_ping_restart_dowork(c);
    }
}
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
struct TYPE_2__ {int /*<<< orphan*/  tmp_int; int /*<<< orphan*/  to_link_addr; int /*<<< orphan*/  to_link; int /*<<< orphan*/  tls_multi; } ;
struct context {TYPE_1__ c2; } ;
typedef  scalar_t__ interval_t ;

/* Variables and functions */
 scalar_t__ BIG_TIMEOUT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int const TLSMP_ACTIVE ; 
 int const TLSMP_KILL ; 
 int /*<<< orphan*/  context_reschedule_sec (struct context*,scalar_t__) ; 
 int /*<<< orphan*/  get_link_socket_info (struct context*) ; 
 int /*<<< orphan*/  interval_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interval_future_trigger (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  interval_schedule_wakeup (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ interval_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 
 int tls_multi_process (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  update_time () ; 

void
check_tls_dowork(struct context *c)
{
    interval_t wakeup = BIG_TIMEOUT;

    if (interval_test(&c->c2.tmp_int))
    {
        const int tmp_status = tls_multi_process
                                   (c->c2.tls_multi, &c->c2.to_link, &c->c2.to_link_addr,
                                   get_link_socket_info(c), &wakeup);
        if (tmp_status == TLSMP_ACTIVE)
        {
            update_time();
            interval_action(&c->c2.tmp_int);
        }
        else if (tmp_status == TLSMP_KILL)
        {
            register_signal(c, SIGTERM, "auth-control-exit");
        }

        interval_future_trigger(&c->c2.tmp_int, wakeup);
    }

    interval_schedule_wakeup(&c->c2.tmp_int, &wakeup);

    if (wakeup)
    {
        context_reschedule_sec(c, wakeup);
    }
}
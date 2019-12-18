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
struct TYPE_3__ {scalar_t__ explicit_exit_notification_time_wait; scalar_t__ tls_multi; } ;
struct context {TYPE_1__ c2; TYPE_2__* sig; } ;
struct TYPE_4__ {scalar_t__ signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_add_routes (struct context*) ; 
 int /*<<< orphan*/  check_connection_established (struct context*) ; 
 int /*<<< orphan*/  check_inactivity_timeout (struct context*) ; 
 int /*<<< orphan*/  check_packet_id_persist_flush (struct context*) ; 
 int /*<<< orphan*/  check_ping_restart (struct context*) ; 
 int /*<<< orphan*/  check_ping_send (struct context*) ; 
 int /*<<< orphan*/  check_push_request (struct context*) ; 
 int /*<<< orphan*/  check_scheduled_exit (struct context*) ; 
 int /*<<< orphan*/  check_send_occ_load_test (struct context*) ; 
 int /*<<< orphan*/  check_send_occ_req (struct context*) ; 
 int /*<<< orphan*/  check_server_poll_timeout (struct context*) ; 
 int /*<<< orphan*/  check_status_file (struct context*) ; 
 int /*<<< orphan*/  pf_check_reload (struct context*) ; 
 int /*<<< orphan*/  process_explicit_exit_notification_timer_wakeup (struct context*) ; 

__attribute__((used)) static void
process_coarse_timers(struct context *c)
{
    /* flush current packet-id to file once per 60
    * seconds if --replay-persist was specified */
    check_packet_id_persist_flush(c);

    /* should we update status file? */
    check_status_file(c);

    /* process connection establishment items */
    check_connection_established(c);

#if P2MP
    /* see if we should send a push_request in response to --pull */
    check_push_request(c);
#endif

#ifdef PLUGIN_PF
    pf_check_reload(c);
#endif

    /* process --route options */
    check_add_routes(c);

    /* possibly exit due to --inactive */
    check_inactivity_timeout(c);
    if (c->sig->signal_received)
    {
        return;
    }

    /* restart if ping not received */
    check_ping_restart(c);
    if (c->sig->signal_received)
    {
        return;
    }

#if P2MP
    if (c->c2.tls_multi)
    {
        check_server_poll_timeout(c);
        if (c->sig->signal_received)
        {
            return;
        }

        check_scheduled_exit(c);
        if (c->sig->signal_received)
        {
            return;
        }
    }
#endif

#ifdef ENABLE_OCC
    /* Should we send an OCC_REQUEST message? */
    check_send_occ_req(c);

    /* Should we send an MTU load test? */
    check_send_occ_load_test(c);

    /* Should we send an OCC_EXIT message to remote? */
    if (c->c2.explicit_exit_notification_time_wait)
    {
        process_explicit_exit_notification_timer_wakeup(c);
    }
#endif

    /* Should we ping the remote? */
    check_ping_send(c);
}
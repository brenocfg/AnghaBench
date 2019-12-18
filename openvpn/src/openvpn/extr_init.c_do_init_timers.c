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
struct TYPE_4__ {int /*<<< orphan*/  tmp_int; int /*<<< orphan*/  packet_id_persist_interval; int /*<<< orphan*/  occ_mtu_load_test_interval; int /*<<< orphan*/  occ_interval; scalar_t__ options_string_remote; scalar_t__ options_string_local; int /*<<< orphan*/  wait_for_connect; int /*<<< orphan*/  ping_rec_interval; int /*<<< orphan*/  ping_send_interval; int /*<<< orphan*/  inactivity_interval; } ;
struct TYPE_3__ {int inactivity_timeout; int ping_send_timeout; int ping_rec_timeout; scalar_t__ packet_id_file; scalar_t__ mtu_test; scalar_t__ occ; } ;
struct context {TYPE_2__ c2; TYPE_1__ options; } ;

/* Variables and functions */
 int OCC_INTERVAL_SECONDS ; 
 int OCC_MTU_LOAD_INTERVAL_SECONDS ; 
 int /*<<< orphan*/  TLS_MODE (struct context*) ; 
 int /*<<< orphan*/  TLS_MULTI_HORIZON ; 
 int /*<<< orphan*/  TLS_MULTI_REFRESH ; 
 int /*<<< orphan*/  event_timeout_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  interval_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  reset_coarse_timers (struct context*) ; 
 int /*<<< orphan*/  update_time () ; 

__attribute__((used)) static void
do_init_timers(struct context *c, bool deferred)
{
    update_time();
    reset_coarse_timers(c);

    /* initialize inactivity timeout */
    if (c->options.inactivity_timeout)
    {
        event_timeout_init(&c->c2.inactivity_interval, c->options.inactivity_timeout, now);
    }

    /* initialize pings */

    if (c->options.ping_send_timeout)
    {
        event_timeout_init(&c->c2.ping_send_interval, c->options.ping_send_timeout, 0);
    }

    if (c->options.ping_rec_timeout)
    {
        event_timeout_init(&c->c2.ping_rec_interval, c->options.ping_rec_timeout, now);
    }

    if (!deferred)
    {
        /* initialize connection establishment timer */
        event_timeout_init(&c->c2.wait_for_connect, 1, now);

#ifdef ENABLE_OCC
        /* initialize occ timers */

        if (c->options.occ
            && !TLS_MODE(c)
            && c->c2.options_string_local && c->c2.options_string_remote)
        {
            event_timeout_init(&c->c2.occ_interval, OCC_INTERVAL_SECONDS, now);
        }

        if (c->options.mtu_test)
        {
            event_timeout_init(&c->c2.occ_mtu_load_test_interval, OCC_MTU_LOAD_INTERVAL_SECONDS, now);
        }
#endif

        /* initialize packet_id persistence timer */
        if (c->options.packet_id_file)
        {
            event_timeout_init(&c->c2.packet_id_persist_interval, 60, now);
        }

        /* initialize tmp_int optimization that limits the number of times we call
         * tls_multi_process in the main event loop */
        interval_init(&c->c2.tmp_int, TLS_MULTI_HORIZON, TLS_MULTI_REFRESH);
    }
}
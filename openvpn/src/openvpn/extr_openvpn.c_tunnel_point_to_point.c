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
struct TYPE_2__ {scalar_t__ event_set_status; } ;
struct context {TYPE_1__ c2; int /*<<< orphan*/  es; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_HARD_USR1_TO_HUP ; 
 int /*<<< orphan*/  CM_P2P ; 
 scalar_t__ ES_TIMEOUT ; 
 scalar_t__ IS_SIG (struct context*) ; 
 int /*<<< orphan*/  P2P_CHECK_SIG () ; 
 int /*<<< orphan*/  PERF_EVENT_LOOP ; 
 int /*<<< orphan*/  close_instance (struct context*) ; 
 int /*<<< orphan*/  context_clear_2 (struct context*) ; 
 int /*<<< orphan*/  init_instance_handle_signals (struct context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_wait (struct context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p2p_iow_flags (struct context*) ; 
 int /*<<< orphan*/  perf_pop () ; 
 int /*<<< orphan*/  perf_push (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_select (struct context*) ; 
 int /*<<< orphan*/  process_io (struct context*) ; 
 int /*<<< orphan*/  uninit_management_callback () ; 

__attribute__((used)) static void
tunnel_point_to_point(struct context *c)
{
    context_clear_2(c);

    /* set point-to-point mode */
    c->mode = CM_P2P;

    /* initialize tunnel instance */
    init_instance_handle_signals(c, c->es, CC_HARD_USR1_TO_HUP);
    if (IS_SIG(c))
    {
        return;
    }

    /* main event loop */
    while (true)
    {
        perf_push(PERF_EVENT_LOOP);

        /* process timers, TLS, etc. */
        pre_select(c);
        P2P_CHECK_SIG();

        /* set up and do the I/O wait */
        io_wait(c, p2p_iow_flags(c));
        P2P_CHECK_SIG();

        /* timeout? */
        if (c->c2.event_set_status == ES_TIMEOUT)
        {
            perf_pop();
            continue;
        }

        /* process the I/O which triggered select */
        process_io(c);
        P2P_CHECK_SIG();

        perf_pop();
    }

    uninit_management_callback();

    /* tear down tunnel instance (unless --persist-tun) */
    close_instance(c);
}
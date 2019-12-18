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
struct TYPE_2__ {int /*<<< orphan*/  explicit_exit_notification_time_wait; int /*<<< orphan*/  explicit_exit_notification_interval; } ;
struct context {TYPE_1__ c2; int /*<<< orphan*/  sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  event_timeout_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halt_non_edge_triggered_signals () ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  reset_coarse_timers (struct context*) ; 
 int /*<<< orphan*/  signal_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_explicit_exit_notification_init(struct context *c)
{
    msg(M_INFO, "SIGTERM received, sending exit notification to peer");
    event_timeout_init(&c->c2.explicit_exit_notification_interval, 1, 0);
    reset_coarse_timers(c);
    signal_reset(c->sig);
    halt_non_edge_triggered_signals();
    c->c2.explicit_exit_notification_time_wait = now;
}
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
struct TYPE_3__ {int /*<<< orphan*/  explicit_exit_notification_interval; } ;
struct context {TYPE_2__* sig; TYPE_1__ c2; } ;
struct TYPE_4__ {scalar_t__ signal_received; scalar_t__ source; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 scalar_t__ SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIGUSR1 ; 
 scalar_t__ SIG_SOURCE_HARD ; 
 scalar_t__ event_timeout_defined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  signal_name (scalar_t__,int) ; 
 int /*<<< orphan*/  signal_reset (TYPE_2__*) ; 

__attribute__((used)) static bool
ignore_restart_signals(struct context *c)
{
    bool ret = false;
#ifdef ENABLE_OCC
    if ( (c->sig->signal_received == SIGUSR1 || c->sig->signal_received == SIGHUP)
         && event_timeout_defined(&c->c2.explicit_exit_notification_interval) )
    {
        if (c->sig->source == SIG_SOURCE_HARD)
        {
            msg(M_INFO, "Ignoring %s received during exit notification",
                signal_name(c->sig->signal_received, true));
            signal_reset(c->sig);
            ret = true;
        }
        else
        {
            msg(M_INFO, "Converting soft %s received during exit notification to SIGTERM",
                signal_name(c->sig->signal_received, true));
            register_signal(c, SIGTERM, "exit-with-notification");
            ret = false;
        }
    }
#endif
    return ret;
}
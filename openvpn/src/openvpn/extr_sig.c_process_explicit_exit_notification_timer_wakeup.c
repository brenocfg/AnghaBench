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
struct TYPE_8__ {scalar_t__ explicit_exit_notification_time_wait; int /*<<< orphan*/  occ_op; int /*<<< orphan*/  explicit_exit_notification_interval; int /*<<< orphan*/  timeval; } ;
struct TYPE_5__ {scalar_t__ explicit_exit_notification; } ;
struct TYPE_6__ {TYPE_1__ ce; } ;
struct context {TYPE_4__ c2; TYPE_3__* sig; TYPE_2__ options; } ;
struct TYPE_7__ {char* signal_text; int /*<<< orphan*/  signal_received; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ETT_DEFAULT ; 
 int /*<<< orphan*/  OCC_EXIT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  event_timeout_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ now ; 

void
process_explicit_exit_notification_timer_wakeup(struct context *c)
{
    if (event_timeout_trigger(&c->c2.explicit_exit_notification_interval,
                              &c->c2.timeval,
                              ETT_DEFAULT))
    {
        ASSERT(c->c2.explicit_exit_notification_time_wait && c->options.ce.explicit_exit_notification);
        if (now >= c->c2.explicit_exit_notification_time_wait + c->options.ce.explicit_exit_notification)
        {
            event_timeout_clear(&c->c2.explicit_exit_notification_interval);
            c->sig->signal_received = SIGTERM;
            c->sig->signal_text = "exit-with-notification";
        }
        else
        {
            c->c2.occ_op = OCC_EXIT;
        }
    }
}
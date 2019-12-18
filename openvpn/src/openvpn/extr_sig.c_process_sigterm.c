#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  explicit_exit_notification_time_wait; } ;
struct TYPE_4__ {scalar_t__ explicit_exit_notification; } ;
struct TYPE_5__ {TYPE_1__ ce; } ;
struct context {TYPE_3__ c2; TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  process_explicit_exit_notification_init (struct context*) ; 

__attribute__((used)) static bool
process_sigterm(struct context *c)
{
    bool ret = true;
#ifdef ENABLE_OCC
    if (c->options.ce.explicit_exit_notification
        && !c->c2.explicit_exit_notification_time_wait)
    {
        process_explicit_exit_notification_init(c);
        ret = false;
    }
#endif
    return ret;
}
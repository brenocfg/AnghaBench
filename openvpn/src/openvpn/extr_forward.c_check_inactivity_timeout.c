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
struct TYPE_4__ {int /*<<< orphan*/  timeval; int /*<<< orphan*/  inactivity_interval; } ;
struct TYPE_3__ {scalar_t__ inactivity_timeout; } ;
struct context {TYPE_2__ c2; TYPE_1__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETT_DEFAULT ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
check_inactivity_timeout(struct context *c)
{
    void check_inactivity_timeout_dowork(struct context *c);

    if (c->options.inactivity_timeout
        && event_timeout_trigger(&c->c2.inactivity_interval, &c->c2.timeval, ETT_DEFAULT))
    {
        check_inactivity_timeout_dowork(c);
    }
}
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
struct TYPE_2__ {int event_set_owned; int /*<<< orphan*/  event_set_max; int /*<<< orphan*/  event_set; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_N_EVENTS ; 
 unsigned int EVENT_METHOD_FAST ; 
 unsigned int EVENT_METHOD_US_TIMEOUT ; 
 int /*<<< orphan*/  event_set_init (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
do_event_set_init(struct context *c,
                  bool need_us_timeout)
{
    unsigned int flags = 0;

    c->c2.event_set_max = BASE_N_EVENTS;

    flags |= EVENT_METHOD_FAST;

    if (need_us_timeout)
    {
        flags |= EVENT_METHOD_US_TIMEOUT;
    }

    c->c2.event_set = event_set_init(&c->c2.event_set_max, flags);
    c->c2.event_set_owned = true;
}
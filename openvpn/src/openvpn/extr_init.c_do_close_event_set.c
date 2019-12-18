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
struct TYPE_2__ {int event_set_owned; int /*<<< orphan*/ * event_set; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
do_close_event_set(struct context *c)
{
    if (c->c2.event_set && c->c2.event_set_owned)
    {
        event_free(c->c2.event_set);
        c->c2.event_set = NULL;
        c->c2.event_set_owned = false;
    }
}
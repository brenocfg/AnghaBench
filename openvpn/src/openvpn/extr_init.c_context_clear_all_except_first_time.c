#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct context_persist {int dummy; } ;
struct context {int first_time; struct context_persist persist; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_clear (struct context*) ; 

void
context_clear_all_except_first_time(struct context *c)
{
    const bool first_time_save = c->first_time;
    const struct context_persist cpsave = c->persist;
    context_clear(c);
    c->first_time = first_time_save;
    c->persist = cpsave;
}
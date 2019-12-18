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
struct context {int /*<<< orphan*/  first_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_restart_pause (struct context*) ; 

__attribute__((used)) static void
do_startup_pause(struct context *c)
{
    if (!c->first_time)
    {
        socket_restart_pause(c);
    }
    else
    {
        do_hold(0); /* do management hold on first context initialization */
    }
}
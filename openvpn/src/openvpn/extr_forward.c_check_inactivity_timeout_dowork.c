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
struct context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  msg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  register_signal (struct context*,int /*<<< orphan*/ ,char*) ; 

void
check_inactivity_timeout_dowork(struct context *c)
{
    msg(M_INFO, "Inactivity timeout (--inactive), exiting");
    register_signal(c, SIGTERM, "inactive");
}
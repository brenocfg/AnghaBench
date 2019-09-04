#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ timer_running; } ;
typedef  TYPE_1__ DATA ;

/* Variables and functions */
 int /*<<< orphan*/  lrotary_check_timer (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  system_get_time () ; 

__attribute__((used)) static void lrotary_timer_done(void *param)
{
  DATA *d = (DATA *) param;

  d->timer_running = 0;

  lrotary_check_timer(d, system_get_time(), 1);
}
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
struct lapb_cb {int /*<<< orphan*/  t1timer; } ;

/* Variables and functions */
 int timer_pending (int /*<<< orphan*/ *) ; 

int lapb_t1timer_running(struct lapb_cb *lapb)
{
	return timer_pending(&lapb->t1timer);
}
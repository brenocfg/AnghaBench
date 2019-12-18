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
struct inet_timewait_sock {int /*<<< orphan*/  tw_timer; } ;

/* Variables and functions */
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inet_twsk_kill (struct inet_timewait_sock*) ; 
 int /*<<< orphan*/  inet_twsk_put (struct inet_timewait_sock*) ; 

void inet_twsk_deschedule_put(struct inet_timewait_sock *tw)
{
	if (del_timer_sync(&tw->tw_timer))
		inet_twsk_kill(tw);
	inet_twsk_put(tw);
}
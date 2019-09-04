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
struct timer_list {int dummy; } ;
struct sctp_association {int dummy; } ;

/* Variables and functions */
 size_t SCTP_EVENT_TIMEOUT_T1_COOKIE ; 
 struct sctp_association* asoc ; 
 struct sctp_association* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_generate_timeout_event (struct sctp_association*,size_t) ; 
 int /*<<< orphan*/ * timers ; 

__attribute__((used)) static void sctp_generate_t1_cookie_event(struct timer_list *t)
{
	struct sctp_association *asoc =
		from_timer(asoc, t, timers[SCTP_EVENT_TIMEOUT_T1_COOKIE]);

	sctp_generate_timeout_event(asoc, SCTP_EVENT_TIMEOUT_T1_COOKIE);
}
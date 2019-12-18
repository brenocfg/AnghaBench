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
struct j1939_session {int /*<<< orphan*/  txtimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL_SOFT ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  j1939_session_get (struct j1939_session*) ; 
 int /*<<< orphan*/  ms_to_ktime (int) ; 

void j1939_tp_schedule_txtimer(struct j1939_session *session, int msec)
{
	j1939_session_get(session);
	hrtimer_start(&session->txtimer, ms_to_ktime(msec),
		      HRTIMER_MODE_REL_SOFT);
}
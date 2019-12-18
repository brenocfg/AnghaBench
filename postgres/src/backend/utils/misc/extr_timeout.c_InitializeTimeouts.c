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
struct TYPE_2__ {int index; int active; int indicator; scalar_t__ fin_time; scalar_t__ start_time; int /*<<< orphan*/ * timeout_handler; } ;

/* Variables and functions */
 int MAX_TIMEOUTS ; 
 int /*<<< orphan*/  SIGALRM ; 
 TYPE_1__* all_timeouts ; 
 int all_timeouts_initialized ; 
 int /*<<< orphan*/  disable_alarm () ; 
 int /*<<< orphan*/  handle_sig_alarm ; 
 scalar_t__ num_active_timeouts ; 
 int /*<<< orphan*/  pqsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
InitializeTimeouts(void)
{
	int			i;

	/* Initialize, or re-initialize, all local state */
	disable_alarm();

	num_active_timeouts = 0;

	for (i = 0; i < MAX_TIMEOUTS; i++)
	{
		all_timeouts[i].index = i;
		all_timeouts[i].active = false;
		all_timeouts[i].indicator = false;
		all_timeouts[i].timeout_handler = NULL;
		all_timeouts[i].start_time = 0;
		all_timeouts[i].fin_time = 0;
	}

	all_timeouts_initialized = true;

	/* Now establish the signal handler */
	pqsignal(SIGALRM, handle_sig_alarm);
}
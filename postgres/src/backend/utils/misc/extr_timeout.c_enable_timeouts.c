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
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  TimeoutId ;
struct TYPE_3__ {int type; int /*<<< orphan*/  fin_time; int /*<<< orphan*/  delay_ms; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ EnableTimeoutParams ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
#define  TMPARAM_AFTER 129 
#define  TMPARAM_AT 128 
 int /*<<< orphan*/  TimestampTzPlusMilliseconds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_alarm () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enable_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_alarm (int /*<<< orphan*/ ) ; 

void
enable_timeouts(const EnableTimeoutParams *timeouts, int count)
{
	TimestampTz now;
	int			i;

	/* Disable timeout interrupts for safety. */
	disable_alarm();

	/* Queue the timeout(s) at the appropriate times. */
	now = GetCurrentTimestamp();

	for (i = 0; i < count; i++)
	{
		TimeoutId	id = timeouts[i].id;
		TimestampTz fin_time;

		switch (timeouts[i].type)
		{
			case TMPARAM_AFTER:
				fin_time = TimestampTzPlusMilliseconds(now,
													   timeouts[i].delay_ms);
				enable_timeout(id, now, fin_time);
				break;

			case TMPARAM_AT:
				enable_timeout(id, now, timeouts[i].fin_time);
				break;

			default:
				elog(ERROR, "unrecognized timeout type %d",
					 (int) timeouts[i].type);
				break;
		}
	}

	/* Set the timer interrupt. */
	schedule_alarm(now);
}
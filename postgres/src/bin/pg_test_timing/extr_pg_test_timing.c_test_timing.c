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
typedef  int uint64 ;
typedef  int int64 ;
typedef  int int32 ;
typedef  int /*<<< orphan*/  instr_time ;

/* Variables and functions */
 int INSTR_TIME_GET_DOUBLE (int /*<<< orphan*/ ) ; 
 int INSTR_TIME_GET_MICROSEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SET_CURRENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTR_TIME_SUBTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INT64CONST (int) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * histogram ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static uint64
test_timing(int32 duration)
{
	uint64		total_time;
	int64		time_elapsed = 0;
	uint64		loop_count = 0;
	uint64		prev,
				cur;
	instr_time	start_time,
				end_time,
				temp;

	total_time = duration > 0 ? duration * INT64CONST(1000000) : 0;

	INSTR_TIME_SET_CURRENT(start_time);
	cur = INSTR_TIME_GET_MICROSEC(start_time);

	while (time_elapsed < total_time)
	{
		int32		diff,
					bits = 0;

		prev = cur;
		INSTR_TIME_SET_CURRENT(temp);
		cur = INSTR_TIME_GET_MICROSEC(temp);
		diff = cur - prev;

		/* Did time go backwards? */
		if (diff < 0)
		{
			fprintf(stderr, _("Detected clock going backwards in time.\n"));
			fprintf(stderr, _("Time warp: %d ms\n"), diff);
			exit(1);
		}

		/* What is the highest bit in the time diff? */
		while (diff)
		{
			diff >>= 1;
			bits++;
		}

		/* Update appropriate duration bucket */
		histogram[bits]++;

		loop_count++;
		INSTR_TIME_SUBTRACT(temp, start_time);
		time_elapsed = INSTR_TIME_GET_MICROSEC(temp);
	}

	INSTR_TIME_SET_CURRENT(end_time);

	INSTR_TIME_SUBTRACT(end_time, start_time);

	printf(_("Per loop time including overhead: %0.2f ns\n"),
		   INSTR_TIME_GET_DOUBLE(end_time) * 1e9 / loop_count);

	return loop_count;
}
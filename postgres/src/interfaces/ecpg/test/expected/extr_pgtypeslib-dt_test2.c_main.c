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
typedef  int /*<<< orphan*/  timestamp ;
typedef  int /*<<< orphan*/  interval ;
typedef  scalar_t__ date ;

/* Variables and functions */
 int /*<<< orphan*/  ECPGdebug (int,int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/  PGTYPESchar_free (char*) ; 
 int /*<<< orphan*/  PGTYPESdate_free (scalar_t__*) ; 
 scalar_t__ PGTYPESdate_from_asc (char*,char**) ; 
 scalar_t__ PGTYPESdate_from_timestamp (int /*<<< orphan*/ ) ; 
 scalar_t__* PGTYPESdate_new () ; 
 char* PGTYPESdate_to_asc (scalar_t__) ; 
 int /*<<< orphan*/  PGTYPESinterval_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGTYPESinterval_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PGTYPESinterval_from_asc (scalar_t__,char**) ; 
 int /*<<< orphan*/ * PGTYPESinterval_new () ; 
 char* PGTYPESinterval_to_asc (int /*<<< orphan*/ *) ; 
 int PGTYPEStimestamp_add_interval (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PGTYPEStimestamp_from_asc (char*,int /*<<< orphan*/ *) ; 
 char* PGTYPEStimestamp_to_asc (int /*<<< orphan*/ ) ; 
 char** dates ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__* intervals ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 char** times ; 

int
main(void)
{
	/* exec sql begin declare section */
		 
		  
		 
		 
		 
	
#line 62 "dt_test2.pgc"
 date date1 ;
 
#line 63 "dt_test2.pgc"
 timestamp ts1 , ts2 ;
 
#line 64 "dt_test2.pgc"
 char * text ;
 
#line 65 "dt_test2.pgc"
 interval * i1 ;
 
#line 66 "dt_test2.pgc"
 date * dc ;
/* exec sql end declare section */
#line 67 "dt_test2.pgc"


	int i, j;
	char *endptr;

	ECPGdebug(1, stderr);

	ts1 = PGTYPEStimestamp_from_asc("2003-12-04 17:34:29", NULL);
	text = PGTYPEStimestamp_to_asc(ts1);

	printf("timestamp: %s\n", text);
	PGTYPESchar_free(text);

	date1 = PGTYPESdate_from_timestamp(ts1);
	dc = PGTYPESdate_new();
	*dc = date1;
	text = PGTYPESdate_to_asc(*dc);
	printf("Date of timestamp: %s\n", text);
	PGTYPESchar_free(text);
	PGTYPESdate_free(dc);

	for (i = 0; dates[i]; i++)
	{
		bool err = false;
		date1 = PGTYPESdate_from_asc(dates[i], &endptr);
		if (date1 == INT_MIN) {
			err = true;
		}
		text = PGTYPESdate_to_asc(date1);
		printf("Date[%d]: %s (%c - %c)\n",
					i, err ? "-" : text,
					endptr ? 'N' : 'Y',
					err ? 'T' : 'F');
		PGTYPESchar_free(text);
		if (!err)
		{
			for (j = 0; times[j]; j++)
			{
				int length = strlen(dates[i])
						+ 1
						+ strlen(times[j])
						+ 1;
				char* t = malloc(length);
				sprintf(t, "%s %s", dates[i], times[j]);
				ts1 = PGTYPEStimestamp_from_asc(t, NULL);
				text = PGTYPEStimestamp_to_asc(ts1);
				printf("TS[%d,%d]: %s\n",
				       i, j, errno ? "-" : text);
				PGTYPESchar_free(text);
				free(t);
			}
		}
	}

	ts1 = PGTYPEStimestamp_from_asc("2004-04-04 23:23:23", NULL);

	for (i = 0; intervals[i]; i++)
	{
		interval *ic;
		i1 = PGTYPESinterval_from_asc(intervals[i], &endptr);
		if (*endptr)
			printf("endptr set to %s\n", endptr);
		if (!i1)
		{
			printf("Error parsing interval %d\n", i);
			continue;
		}
		j = PGTYPEStimestamp_add_interval(&ts1, i1, &ts2);
		if (j < 0)
			continue;
		text = PGTYPESinterval_to_asc(i1);
		printf("interval[%d]: %s\n", i, text ? text : "-");
		PGTYPESchar_free(text);

		ic = PGTYPESinterval_new();
		PGTYPESinterval_copy(i1, ic);
		text = PGTYPESinterval_to_asc(i1);
		printf("interval_copy[%d]: %s\n", i, text ? text : "-");
		PGTYPESchar_free(text);
		PGTYPESinterval_free(ic);
		PGTYPESinterval_free(i1);
	}

	return 0;
}
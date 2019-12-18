#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {void* zone_type; scalar_t__ is_localtime; scalar_t__ dst; scalar_t__ z; scalar_t__ us; void* s; void* i; void* h; void* m; void* d; void* y; } ;
typedef  TYPE_1__ timelib_time ;
struct TYPE_19__ {void* days; scalar_t__ first_last_day_of; scalar_t__ weekday_behavior; scalar_t__ weekday; scalar_t__ s; scalar_t__ i; scalar_t__ h; scalar_t__ m; scalar_t__ d; scalar_t__ y; } ;
typedef  TYPE_2__ timelib_rel_time ;
struct TYPE_20__ {int /*<<< orphan*/ * error_messages; scalar_t__ error_count; int /*<<< orphan*/ * warning_messages; scalar_t__ warning_count; } ;
typedef  TYPE_3__ timelib_error_container ;
typedef  int /*<<< orphan*/  in ;
struct TYPE_21__ {int recurrences; scalar_t__ have_recurrences; TYPE_2__* period; scalar_t__ have_period; TYPE_1__* end; scalar_t__ have_end_date; TYPE_1__* begin; scalar_t__ have_begin_date; TYPE_3__* errors; struct TYPE_21__* str; struct TYPE_21__* cur; struct TYPE_21__* lim; } ;
typedef  TYPE_4__ Scanner ;

/* Variables and functions */
 int EOI ; 
 void* TIMELIB_UNSET ; 
 void* TIMELIB_ZONETYPE_OFFSET ; 
 int YYMAXFILL ; 
 int /*<<< orphan*/  add_error (TYPE_4__*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int scan (TYPE_4__*) ; 
 int /*<<< orphan*/  timelib_error_container_dtor (TYPE_3__*) ; 
 int /*<<< orphan*/  timelib_free (TYPE_4__*) ; 
 void* timelib_malloc (int) ; 
 TYPE_2__* timelib_rel_time_ctor () ; 
 int /*<<< orphan*/  timelib_rel_time_dtor (TYPE_2__*) ; 
 void* timelib_time_ctor () ; 
 int /*<<< orphan*/  timelib_time_dtor (TYPE_1__*) ; 

void timelib_strtointerval(char *s, size_t len,
                           timelib_time **begin, timelib_time **end,
						   timelib_rel_time **period, int *recurrences,
						   timelib_error_container **errors)
{
	Scanner in;
	int t;
	char *e = s + len - 1;

	memset(&in, 0, sizeof(in));
	in.errors = timelib_malloc(sizeof(timelib_error_container));
	in.errors->warning_count = 0;
	in.errors->warning_messages = NULL;
	in.errors->error_count = 0;
	in.errors->error_messages = NULL;

	if (len > 0) {
		while (isspace(*s) && s < e) {
			s++;
		}
		while (isspace(*e) && e > s) {
			e--;
		}
	}
	if (e - s < 0) {
		add_error(&in, "Empty string");
		if (errors) {
			*errors = in.errors;
		} else {
			timelib_error_container_dtor(in.errors);
		}
		return;
	}
	e++;

	/* init cursor */
	in.str = timelib_malloc((e - s) + YYMAXFILL);
	memset(in.str, 0, (e - s) + YYMAXFILL);
	memcpy(in.str, s, (e - s));
	in.lim = in.str + (e - s) + YYMAXFILL;
	in.cur = in.str;

	/* init value containers */
	in.begin = timelib_time_ctor();
	in.begin->y = TIMELIB_UNSET;
	in.begin->d = TIMELIB_UNSET;
	in.begin->m = TIMELIB_UNSET;
	in.begin->h = TIMELIB_UNSET;
	in.begin->i = TIMELIB_UNSET;
	in.begin->s = TIMELIB_UNSET;
	in.begin->us = 0;
	in.begin->z = 0;
	in.begin->dst = 0;
	in.begin->is_localtime = 0;
	in.begin->zone_type = TIMELIB_ZONETYPE_OFFSET;

	in.end = timelib_time_ctor();
	in.end->y = TIMELIB_UNSET;
	in.end->d = TIMELIB_UNSET;
	in.end->m = TIMELIB_UNSET;
	in.end->h = TIMELIB_UNSET;
	in.end->i = TIMELIB_UNSET;
	in.end->s = TIMELIB_UNSET;
	in.end->us = 0;
	in.end->z = 0;
	in.end->dst = 0;
	in.end->is_localtime = 0;
	in.end->zone_type = TIMELIB_ZONETYPE_OFFSET;

	in.period = timelib_rel_time_ctor();
	in.period->y = 0;
	in.period->d = 0;
	in.period->m = 0;
	in.period->h = 0;
	in.period->i = 0;
	in.period->s = 0;
	in.period->weekday = 0;
	in.period->weekday_behavior = 0;
	in.period->first_last_day_of = 0;
	in.period->days = TIMELIB_UNSET;

	in.recurrences = 1;

	do {
		t = scan(&in);
#ifdef DEBUG_PARSER
		printf("%d\n", t);
#endif
	} while(t != EOI);

	timelib_free(in.str);
	if (errors) {
		*errors = in.errors;
	} else {
		timelib_error_container_dtor(in.errors);
	}
	if (in.have_begin_date) {
		*begin = in.begin;
	} else {
		timelib_time_dtor(in.begin);
	}
	if (in.have_end_date) {
		*end   = in.end;
	} else {
		timelib_time_dtor(in.end);
	}
	if (in.have_period) {
		*period = in.period;
	} else {
		timelib_rel_time_dtor(in.period);
	}
	if (in.have_recurrences) {
		*recurrences = in.recurrences;
	}
}
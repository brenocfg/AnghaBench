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
struct rule {int r_time; int /*<<< orphan*/  r_day; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_week; int /*<<< orphan*/  r_mon; } ;

/* Variables and functions */
 int DAYSPERLYEAR ; 
 int DAYSPERNYEAR ; 
 int DAYSPERWEEK ; 
 int /*<<< orphan*/  DAY_OF_YEAR ; 
 int /*<<< orphan*/  JULIAN_DAY ; 
 int MONSPERYEAR ; 
 int /*<<< orphan*/  MONTH_NTH_DAY_OF_WEEK ; 
 int SECSPERHOUR ; 
 char* getnum (char const*,int /*<<< orphan*/ *,int,int) ; 
 char* getoffset (char const*,int*) ; 
 scalar_t__ is_digit (char const) ; 

__attribute__((used)) static const char *
getrule(const char *strp, struct rule *const rulep)
{
	if (*strp == 'J')
	{
		/*
		 * Julian day.
		 */
		rulep->r_type = JULIAN_DAY;
		++strp;
		strp = getnum(strp, &rulep->r_day, 1, DAYSPERNYEAR);
	}
	else if (*strp == 'M')
	{
		/*
		 * Month, week, day.
		 */
		rulep->r_type = MONTH_NTH_DAY_OF_WEEK;
		++strp;
		strp = getnum(strp, &rulep->r_mon, 1, MONSPERYEAR);
		if (strp == NULL)
			return NULL;
		if (*strp++ != '.')
			return NULL;
		strp = getnum(strp, &rulep->r_week, 1, 5);
		if (strp == NULL)
			return NULL;
		if (*strp++ != '.')
			return NULL;
		strp = getnum(strp, &rulep->r_day, 0, DAYSPERWEEK - 1);
	}
	else if (is_digit(*strp))
	{
		/*
		 * Day of year.
		 */
		rulep->r_type = DAY_OF_YEAR;
		strp = getnum(strp, &rulep->r_day, 0, DAYSPERLYEAR - 1);
	}
	else
		return NULL;			/* invalid format */
	if (strp == NULL)
		return NULL;
	if (*strp == '/')
	{
		/*
		 * Time specified.
		 */
		++strp;
		strp = getoffset(strp, &rulep->r_time);
	}
	else
		rulep->r_time = 2 * SECSPERHOUR;	/* default = 2:00:00 */
	return strp;
}
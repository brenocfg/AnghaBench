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

/* Variables and functions */
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  LC_MONETARY ; 
 int /*<<< orphan*/  LC_NUMERIC ; 
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  check_locale_name (int /*<<< orphan*/ ,char*,char**) ; 
 char* lc_collate ; 
 char* lc_ctype ; 
 char* lc_messages ; 
 char* lc_monetary ; 
 char* lc_numeric ; 
 char* lc_time ; 
 char* locale ; 

__attribute__((used)) static void
setlocales(void)
{
	char	   *canonname;

	/* set empty lc_* values to locale config if set */

	if (locale)
	{
		if (!lc_ctype)
			lc_ctype = locale;
		if (!lc_collate)
			lc_collate = locale;
		if (!lc_numeric)
			lc_numeric = locale;
		if (!lc_time)
			lc_time = locale;
		if (!lc_monetary)
			lc_monetary = locale;
		if (!lc_messages)
			lc_messages = locale;
	}

	/*
	 * canonicalize locale names, and obtain any missing values from our
	 * current environment
	 */

	check_locale_name(LC_CTYPE, lc_ctype, &canonname);
	lc_ctype = canonname;
	check_locale_name(LC_COLLATE, lc_collate, &canonname);
	lc_collate = canonname;
	check_locale_name(LC_NUMERIC, lc_numeric, &canonname);
	lc_numeric = canonname;
	check_locale_name(LC_TIME, lc_time, &canonname);
	lc_time = canonname;
	check_locale_name(LC_MONETARY, lc_monetary, &canonname);
	lc_monetary = canonname;
#if defined(LC_MESSAGES) && !defined(WIN32)
	check_locale_name(LC_MESSAGES, lc_messages, &canonname);
	lc_messages = canonname;
#else
	/* when LC_MESSAGES is not available, use the LC_CTYPE setting */
	check_locale_name(LC_CTYPE, lc_messages, &canonname);
	lc_messages = canonname;
#endif
}
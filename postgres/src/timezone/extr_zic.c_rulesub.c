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
struct rule {int r_month; int r_todisstd; int r_todisut; int r_loyear; int r_hiyear; scalar_t__ r_dycode; int r_wday; int r_dayofmonth; int /*<<< orphan*/ * r_yrtype; int /*<<< orphan*/  r_hiwasnum; int /*<<< orphan*/  r_lowasnum; int /*<<< orphan*/  r_tod; } ;
struct lookup {int l_value; } ;

/* Variables and functions */
 scalar_t__ DC_DOM ; 
 scalar_t__ DC_DOWGEQ ; 
 void* DC_DOWLEQ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
#define  YR_MAXIMUM 130 
#define  YR_MINIMUM 129 
#define  YR_ONLY 128 
 void* ZIC_MAX ; 
 void* ZIC_MIN ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  begin_years ; 
 struct lookup* byword (char const*,int /*<<< orphan*/ ) ; 
 void* ecpyalloc (char const*) ; 
 int /*<<< orphan*/  end_years ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gethms (char*,char*) ; 
 int /*<<< orphan*/  lasts ; 
 scalar_t__** len_months ; 
 int lowerit (char) ; 
 int /*<<< orphan*/  mon_names ; 
 char* progname ; 
 int sscanf (char const*,char*,int*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  warning (char*,char const*) ; 
 int /*<<< orphan*/  wday_names ; 

__attribute__((used)) static void
rulesub(struct rule *rp, const char *loyearp, const char *hiyearp,
		const char *typep, const char *monthp, const char *dayp,
		const char *timep)
{
	const struct lookup *lp;
	const char *cp;
	char	   *dp;
	char	   *ep;
	char		xs;

	/* PG: year_tmp is to avoid sscanf portability issues */
	int			year_tmp;

	if ((lp = byword(monthp, mon_names)) == NULL)
	{
		error(_("invalid month name"));
		return;
	}
	rp->r_month = lp->l_value;
	rp->r_todisstd = false;
	rp->r_todisut = false;
	dp = ecpyalloc(timep);
	if (*dp != '\0')
	{
		ep = dp + strlen(dp) - 1;
		switch (lowerit(*ep))
		{
			case 's':			/* Standard */
				rp->r_todisstd = true;
				rp->r_todisut = false;
				*ep = '\0';
				break;
			case 'w':			/* Wall */
				rp->r_todisstd = false;
				rp->r_todisut = false;
				*ep = '\0';
				break;
			case 'g':			/* Greenwich */
			case 'u':			/* Universal */
			case 'z':			/* Zulu */
				rp->r_todisstd = true;
				rp->r_todisut = true;
				*ep = '\0';
				break;
		}
	}
	rp->r_tod = gethms(dp, _("invalid time of day"));
	free(dp);

	/*
	 * Year work.
	 */
	cp = loyearp;
	lp = byword(cp, begin_years);
	rp->r_lowasnum = lp == NULL;
	if (!rp->r_lowasnum)
		switch (lp->l_value)
		{
			case YR_MINIMUM:
				rp->r_loyear = ZIC_MIN;
				break;
			case YR_MAXIMUM:
				rp->r_loyear = ZIC_MAX;
				break;
			default:			/* "cannot happen" */
				fprintf(stderr,
						_("%s: panic: Invalid l_value %d\n"),
						progname, lp->l_value);
				exit(EXIT_FAILURE);
		}
	else if (sscanf(cp, "%d%c", &year_tmp, &xs) == 1)
		rp->r_loyear = year_tmp;
	else
	{
		error(_("invalid starting year"));
		return;
	}
	cp = hiyearp;
	lp = byword(cp, end_years);
	rp->r_hiwasnum = lp == NULL;
	if (!rp->r_hiwasnum)
		switch (lp->l_value)
		{
			case YR_MINIMUM:
				rp->r_hiyear = ZIC_MIN;
				break;
			case YR_MAXIMUM:
				rp->r_hiyear = ZIC_MAX;
				break;
			case YR_ONLY:
				rp->r_hiyear = rp->r_loyear;
				break;
			default:			/* "cannot happen" */
				fprintf(stderr,
						_("%s: panic: Invalid l_value %d\n"),
						progname, lp->l_value);
				exit(EXIT_FAILURE);
		}
	else if (sscanf(cp, "%d%c", &year_tmp, &xs) == 1)
		rp->r_hiyear = year_tmp;
	else
	{
		error(_("invalid ending year"));
		return;
	}
	if (rp->r_loyear > rp->r_hiyear)
	{
		error(_("starting year greater than ending year"));
		return;
	}
	if (*typep == '\0')
		rp->r_yrtype = NULL;
	else
	{
		if (rp->r_loyear == rp->r_hiyear)
		{
			error(_("typed single year"));
			return;
		}
		warning(_("year type \"%s\" is obsolete; use \"-\" instead"),
				typep);
		rp->r_yrtype = ecpyalloc(typep);
	}

	/*
	 * Day work. Accept things such as: 1 lastSunday last-Sunday
	 * (undocumented; warn about this) Sun<=20 Sun>=7
	 */
	dp = ecpyalloc(dayp);
	if ((lp = byword(dp, lasts)) != NULL)
	{
		rp->r_dycode = DC_DOWLEQ;
		rp->r_wday = lp->l_value;
		rp->r_dayofmonth = len_months[1][rp->r_month];
	}
	else
	{
		if ((ep = strchr(dp, '<')) != NULL)
			rp->r_dycode = DC_DOWLEQ;
		else if ((ep = strchr(dp, '>')) != NULL)
			rp->r_dycode = DC_DOWGEQ;
		else
		{
			ep = dp;
			rp->r_dycode = DC_DOM;
		}
		if (rp->r_dycode != DC_DOM)
		{
			*ep++ = 0;
			if (*ep++ != '=')
			{
				error(_("invalid day of month"));
				free(dp);
				return;
			}
			if ((lp = byword(dp, wday_names)) == NULL)
			{
				error(_("invalid weekday name"));
				free(dp);
				return;
			}
			rp->r_wday = lp->l_value;
		}
		if (sscanf(ep, "%d%c", &rp->r_dayofmonth, &xs) != 1 ||
			rp->r_dayofmonth <= 0 ||
			(rp->r_dayofmonth > len_months[1][rp->r_month]))
		{
			error(_("invalid day of month"));
			free(dp);
			return;
		}
	}
	free(dp);
}
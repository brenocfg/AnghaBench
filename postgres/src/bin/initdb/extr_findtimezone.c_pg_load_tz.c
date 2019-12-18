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
struct TYPE_3__ {int /*<<< orphan*/  TZname; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ pg_tz ;

/* Variables and functions */
 scalar_t__ TZ_STRLEN_MAX ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ tzload (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tzparse (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static pg_tz *
pg_load_tz(const char *name)
{
	static pg_tz tz;

	if (strlen(name) > TZ_STRLEN_MAX)
		return NULL;			/* not going to fit */

	/*
	 * "GMT" is always sent to tzparse(); see comments for pg_tzset().
	 */
	if (strcmp(name, "GMT") == 0)
	{
		if (!tzparse(name, &tz.state, true))
		{
			/* This really, really should not happen ... */
			return NULL;
		}
	}
	else if (tzload(name, NULL, &tz.state, true) != 0)
	{
		if (name[0] == ':' || !tzparse(name, &tz.state, false))
		{
			return NULL;		/* unknown timezone */
		}
	}

	strcpy(tz.TZname, name);

	return &tz;
}
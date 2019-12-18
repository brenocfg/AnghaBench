#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tzstate ;
struct state {int dummy; } ;
struct TYPE_5__ {char* TZname; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {TYPE_2__ tz; } ;
typedef  TYPE_1__ pg_tz_cache ;
typedef  TYPE_2__ pg_tz ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int TZ_STRLEN_MAX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timezone_hashtable () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct state*,int) ; 
 int /*<<< orphan*/  pg_toupper (unsigned char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  timezone_cache ; 
 scalar_t__ tzload (char*,char*,struct state*,int) ; 
 int /*<<< orphan*/  tzparse (char*,struct state*,int) ; 

pg_tz *
pg_tzset(const char *name)
{
	pg_tz_cache *tzp;
	struct state tzstate;
	char		uppername[TZ_STRLEN_MAX + 1];
	char		canonname[TZ_STRLEN_MAX + 1];
	char	   *p;

	if (strlen(name) > TZ_STRLEN_MAX)
		return NULL;			/* not going to fit */

	if (!timezone_cache)
		if (!init_timezone_hashtable())
			return NULL;

	/*
	 * Upcase the given name to perform a case-insensitive hashtable search.
	 * (We could alternatively downcase it, but we prefer upcase so that we
	 * can get consistently upcased results from tzparse() in case the name is
	 * a POSIX-style timezone spec.)
	 */
	p = uppername;
	while (*name)
		*p++ = pg_toupper((unsigned char) *name++);
	*p = '\0';

	tzp = (pg_tz_cache *) hash_search(timezone_cache,
									  uppername,
									  HASH_FIND,
									  NULL);
	if (tzp)
	{
		/* Timezone found in cache, nothing more to do */
		return &tzp->tz;
	}

	/*
	 * "GMT" is always sent to tzparse(), as per discussion above.
	 */
	if (strcmp(uppername, "GMT") == 0)
	{
		if (!tzparse(uppername, &tzstate, true))
		{
			/* This really, really should not happen ... */
			elog(ERROR, "could not initialize GMT time zone");
		}
		/* Use uppercase name as canonical */
		strcpy(canonname, uppername);
	}
	else if (tzload(uppername, canonname, &tzstate, true) != 0)
	{
		if (uppername[0] == ':' || !tzparse(uppername, &tzstate, false))
		{
			/* Unknown timezone. Fail our call instead of loading GMT! */
			return NULL;
		}
		/* For POSIX timezone specs, use uppercase name as canonical */
		strcpy(canonname, uppername);
	}

	/* Save timezone in the cache */
	tzp = (pg_tz_cache *) hash_search(timezone_cache,
									  uppername,
									  HASH_ENTER,
									  NULL);

	/* hash_search already copied uppername into the hash key */
	strcpy(tzp->tz.TZname, canonname);
	memcpy(&tzp->tz.state, &tzstate, sizeof(tzstate));

	return &tzp->tz;
}
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
typedef  long zic_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int TZ_MAX_TYPES ; 
 int /*<<< orphan*/  _ (char*) ; 
 int charcnt ; 
 int /*<<< orphan*/ * chars ; 
 int* desigidx ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int* isdsts ; 
 int /*<<< orphan*/  newabbr (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int* ttisstds ; 
 int* ttisuts ; 
 int typecnt ; 
 long* utoffs ; 
 int /*<<< orphan*/  want_bloat () ; 

__attribute__((used)) static int
addtype(zic_t utoff, char const *abbr, bool isdst, bool ttisstd, bool ttisut)
{
	int			i,
				j;

	if (!(-1L - 2147483647L <= utoff && utoff <= 2147483647L))
	{
		error(_("UT offset out of range"));
		exit(EXIT_FAILURE);
	}
	if (!want_bloat())
		ttisstd = ttisut = false;

	for (j = 0; j < charcnt; ++j)
		if (strcmp(&chars[j], abbr) == 0)
			break;
	if (j == charcnt)
		newabbr(abbr);
	else
	{
		/* If there's already an entry, return its index.  */
		for (i = 0; i < typecnt; i++)
			if (utoff == utoffs[i] && isdst == isdsts[i] && j == desigidx[i]
				&& ttisstd == ttisstds[i] && ttisut == ttisuts[i])
				return i;
	}

	/*
	 * There isn't one; add a new one, unless there are already too many.
	 */
	if (typecnt >= TZ_MAX_TYPES)
	{
		error(_("too many local time types"));
		exit(EXIT_FAILURE);
	}
	i = typecnt++;
	utoffs[i] = utoff;
	isdsts[i] = isdst;
	ttisstds[i] = ttisstd;
	ttisuts[i] = ttisut;
	desigidx[i] = j;
	return i;
}
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
struct TYPE_3__ {scalar_t__ provider; int /*<<< orphan*/  deterministic; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ C_COLLATION_OID ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INDETERMINATE_COLLATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_1BYTE ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_1BYTE_L ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_C ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_ICU ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_WIDE ; 
 int /*<<< orphan*/  PG_REGEX_LOCALE_WIDE_L ; 
 scalar_t__ PG_UTF8 ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ lc_ctype_is_c (scalar_t__) ; 
 TYPE_1__* pg_newlocale_from_collation (scalar_t__) ; 
 scalar_t__ pg_regex_collation ; 
 TYPE_1__* pg_regex_locale ; 
 int /*<<< orphan*/  pg_regex_strategy ; 

void
pg_set_regex_collation(Oid collation)
{
	if (lc_ctype_is_c(collation))
	{
		/* C/POSIX collations use this path regardless of database encoding */
		pg_regex_strategy = PG_REGEX_LOCALE_C;
		pg_regex_locale = 0;
		pg_regex_collation = C_COLLATION_OID;
	}
	else
	{
		if (collation == DEFAULT_COLLATION_OID)
			pg_regex_locale = 0;
		else if (OidIsValid(collation))
		{
			/*
			 * NB: pg_newlocale_from_collation will fail if not HAVE_LOCALE_T;
			 * the case of pg_regex_locale != 0 but not HAVE_LOCALE_T does not
			 * have to be considered below.
			 */
			pg_regex_locale = pg_newlocale_from_collation(collation);
		}
		else
		{
			/*
			 * This typically means that the parser could not resolve a
			 * conflict of implicit collations, so report it that way.
			 */
			ereport(ERROR,
					(errcode(ERRCODE_INDETERMINATE_COLLATION),
					 errmsg("could not determine which collation to use for regular expression"),
					 errhint("Use the COLLATE clause to set the collation explicitly.")));
		}

		if (pg_regex_locale && !pg_regex_locale->deterministic)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("nondeterministic collations are not supported for regular expressions")));

#ifdef USE_ICU
		if (pg_regex_locale && pg_regex_locale->provider == COLLPROVIDER_ICU)
			pg_regex_strategy = PG_REGEX_LOCALE_ICU;
		else
#endif
		if (GetDatabaseEncoding() == PG_UTF8)
		{
			if (pg_regex_locale)
				pg_regex_strategy = PG_REGEX_LOCALE_WIDE_L;
			else
				pg_regex_strategy = PG_REGEX_LOCALE_WIDE;
		}
		else
		{
			if (pg_regex_locale)
				pg_regex_strategy = PG_REGEX_LOCALE_1BYTE_L;
			else
				pg_regex_strategy = PG_REGEX_LOCALE_1BYTE;
		}

		pg_regex_collation = collation;
	}
}
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
typedef  TYPE_1__* pg_locale_t ;
struct TYPE_3__ {int /*<<< orphan*/  deterministic; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 int MB_MatchText (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PG_UTF8 ; 
 int SB_MatchText (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 int UTF8_MatchText (char const*,int,char const*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  lc_ctype_is_c (scalar_t__) ; 
 int pg_database_encoding_max_length () ; 
 TYPE_1__* pg_newlocale_from_collation (scalar_t__) ; 

__attribute__((used)) static inline int
GenericMatchText(const char *s, int slen, const char *p, int plen, Oid collation)
{
	if (collation && !lc_ctype_is_c(collation) && collation != DEFAULT_COLLATION_OID)
	{
		pg_locale_t locale = pg_newlocale_from_collation(collation);

		if (locale && !locale->deterministic)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("nondeterministic collations are not supported for LIKE")));
	}

	if (pg_database_encoding_max_length() == 1)
		return SB_MatchText(s, slen, p, plen, 0, true);
	else if (GetDatabaseEncoding() == PG_UTF8)
		return UTF8_MatchText(s, slen, p, plen, 0, true);
	else
		return MB_MatchText(s, slen, p, plen, 0, true);
}
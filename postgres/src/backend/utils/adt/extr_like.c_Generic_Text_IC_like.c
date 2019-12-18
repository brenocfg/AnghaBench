#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
typedef  TYPE_1__* pg_locale_t ;
struct TYPE_4__ {scalar_t__ provider; int /*<<< orphan*/  deterministic; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1Coll (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INDETERMINATE_COLLATION ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 int MB_MatchText (char*,int,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 scalar_t__ PG_UTF8 ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int SB_IMatchText (char*,int,char*,int,TYPE_1__*,int) ; 
 int UTF8_MatchText (char*,int,char*,int,int /*<<< orphan*/ ,int) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ lc_ctype_is_c (scalar_t__) ; 
 int /*<<< orphan*/  lower ; 
 int pg_database_encoding_max_length () ; 
 TYPE_1__* pg_newlocale_from_collation (scalar_t__) ; 

__attribute__((used)) static inline int
Generic_Text_IC_like(text *str, text *pat, Oid collation)
{
	char	   *s,
			   *p;
	int			slen,
				plen;
	pg_locale_t locale = 0;
	bool		locale_is_c = false;

	if (lc_ctype_is_c(collation))
		locale_is_c = true;
	else if (collation != DEFAULT_COLLATION_OID)
	{
		if (!OidIsValid(collation))
		{
			/*
			 * This typically means that the parser could not resolve a
			 * conflict of implicit collations, so report it that way.
			 */
			ereport(ERROR,
					(errcode(ERRCODE_INDETERMINATE_COLLATION),
					 errmsg("could not determine which collation to use for ILIKE"),
					 errhint("Use the COLLATE clause to set the collation explicitly.")));
		}
		locale = pg_newlocale_from_collation(collation);

		if (locale && !locale->deterministic)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("nondeterministic collations are not supported for ILIKE")));
	}

	/*
	 * For efficiency reasons, in the single byte case we don't call lower()
	 * on the pattern and text, but instead call SB_lower_char on each
	 * character.  In the multi-byte case we don't have much choice :-(. Also,
	 * ICU does not support single-character case folding, so we go the long
	 * way.
	 */

	if (pg_database_encoding_max_length() > 1 || (locale && locale->provider == COLLPROVIDER_ICU))
	{
		pat = DatumGetTextPP(DirectFunctionCall1Coll(lower, collation,
													 PointerGetDatum(pat)));
		p = VARDATA_ANY(pat);
		plen = VARSIZE_ANY_EXHDR(pat);
		str = DatumGetTextPP(DirectFunctionCall1Coll(lower, collation,
													 PointerGetDatum(str)));
		s = VARDATA_ANY(str);
		slen = VARSIZE_ANY_EXHDR(str);
		if (GetDatabaseEncoding() == PG_UTF8)
			return UTF8_MatchText(s, slen, p, plen, 0, true);
		else
			return MB_MatchText(s, slen, p, plen, 0, true);
	}
	else
	{
		p = VARDATA_ANY(pat);
		plen = VARSIZE_ANY_EXHDR(pat);
		s = VARDATA_ANY(str);
		slen = VARSIZE_ANY_EXHDR(str);
		return SB_IMatchText(s, slen, p, plen, locale, locale_is_c);
	}
}
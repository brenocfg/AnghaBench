#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pg_locale_t ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_6__ {scalar_t__ consttype; int /*<<< orphan*/  constvalue; } ;
typedef  int /*<<< orphan*/  Selectivity ;
typedef  scalar_t__ Pointer ;
typedef  int /*<<< orphan*/  Pattern_Prefix_Status ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ BYTEAOID ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/ * DatumGetByteaPP (int /*<<< orphan*/ ) ; 
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INDETERMINATE_COLLATION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  Pattern_Prefix_Exact ; 
 int /*<<< orphan*/  Pattern_Prefix_None ; 
 int /*<<< orphan*/  Pattern_Prefix_Partial ; 
 scalar_t__ TEXTOID ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ lc_ctype_is_c (scalar_t__) ; 
 int /*<<< orphan*/  like_selectivity (char*,int,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* palloc (int) ; 
 scalar_t__ pattern_char_isalpha (char,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_database_encoding_max_length () ; 
 int /*<<< orphan*/  pg_newlocale_from_collation (scalar_t__) ; 
 TYPE_1__* string_to_bytea_const (char*,int) ; 
 TYPE_1__* string_to_const (char*,scalar_t__) ; 
 int strlen (char*) ; 

__attribute__((used)) static Pattern_Prefix_Status
like_fixed_prefix(Const *patt_const, bool case_insensitive, Oid collation,
				  Const **prefix_const, Selectivity *rest_selec)
{
	char	   *match;
	char	   *patt;
	int			pattlen;
	Oid			typeid = patt_const->consttype;
	int			pos,
				match_pos;
	bool		is_multibyte = (pg_database_encoding_max_length() > 1);
	pg_locale_t locale = 0;
	bool		locale_is_c = false;

	/* the right-hand const is type text or bytea */
	Assert(typeid == BYTEAOID || typeid == TEXTOID);

	if (case_insensitive)
	{
		if (typeid == BYTEAOID)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("case insensitive matching not supported on type bytea")));

		/* If case-insensitive, we need locale info */
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
		}
	}

	if (typeid != BYTEAOID)
	{
		patt = TextDatumGetCString(patt_const->constvalue);
		pattlen = strlen(patt);
	}
	else
	{
		bytea	   *bstr = DatumGetByteaPP(patt_const->constvalue);

		pattlen = VARSIZE_ANY_EXHDR(bstr);
		patt = (char *) palloc(pattlen);
		memcpy(patt, VARDATA_ANY(bstr), pattlen);
		Assert((Pointer) bstr == DatumGetPointer(patt_const->constvalue));
	}

	match = palloc(pattlen + 1);
	match_pos = 0;
	for (pos = 0; pos < pattlen; pos++)
	{
		/* % and _ are wildcard characters in LIKE */
		if (patt[pos] == '%' ||
			patt[pos] == '_')
			break;

		/* Backslash escapes the next character */
		if (patt[pos] == '\\')
		{
			pos++;
			if (pos >= pattlen)
				break;
		}

		/* Stop if case-varying character (it's sort of a wildcard) */
		if (case_insensitive &&
			pattern_char_isalpha(patt[pos], is_multibyte, locale, locale_is_c))
			break;

		match[match_pos++] = patt[pos];
	}

	match[match_pos] = '\0';

	if (typeid != BYTEAOID)
		*prefix_const = string_to_const(match, typeid);
	else
		*prefix_const = string_to_bytea_const(match, match_pos);

	if (rest_selec != NULL)
		*rest_selec = like_selectivity(&patt[pos], pattlen - pos,
									   case_insensitive);

	pfree(patt);
	pfree(match);

	/* in LIKE, an empty pattern is an exact match! */
	if (pos == pattlen)
		return Pattern_Prefix_Exact;	/* reached end of pattern, so exact */

	if (match_pos > 0)
		return Pattern_Prefix_Partial;

	return Pattern_Prefix_None;
}
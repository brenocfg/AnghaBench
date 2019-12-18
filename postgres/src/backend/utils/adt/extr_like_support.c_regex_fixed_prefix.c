#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ consttype; int /*<<< orphan*/  constvalue; } ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  Pattern_Prefix_Status ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ Const ;

/* Variables and functions */
 scalar_t__ BYTEAOID ; 
 int /*<<< orphan*/  DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  Pattern_Prefix_Exact ; 
 int /*<<< orphan*/  Pattern_Prefix_None ; 
 int /*<<< orphan*/  Pattern_Prefix_Partial ; 
 char* TextDatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 double regex_selectivity (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* regexp_fixed_prefix (int /*<<< orphan*/ ,int,scalar_t__,int*) ; 
 TYPE_1__* string_to_const (char*,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static Pattern_Prefix_Status
regex_fixed_prefix(Const *patt_const, bool case_insensitive, Oid collation,
				   Const **prefix_const, Selectivity *rest_selec)
{
	Oid			typeid = patt_const->consttype;
	char	   *prefix;
	bool		exact;

	/*
	 * Should be unnecessary, there are no bytea regex operators defined. As
	 * such, it should be noted that the rest of this function has *not* been
	 * made safe for binary (possibly NULL containing) strings.
	 */
	if (typeid == BYTEAOID)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("regular-expression matching not supported on type bytea")));

	/* Use the regexp machinery to extract the prefix, if any */
	prefix = regexp_fixed_prefix(DatumGetTextPP(patt_const->constvalue),
								 case_insensitive, collation,
								 &exact);

	if (prefix == NULL)
	{
		*prefix_const = NULL;

		if (rest_selec != NULL)
		{
			char	   *patt = TextDatumGetCString(patt_const->constvalue);

			*rest_selec = regex_selectivity(patt, strlen(patt),
											case_insensitive,
											0);
			pfree(patt);
		}

		return Pattern_Prefix_None;
	}

	*prefix_const = string_to_const(prefix, typeid);

	if (rest_selec != NULL)
	{
		if (exact)
		{
			/* Exact match, so there's no additional selectivity */
			*rest_selec = 1.0;
		}
		else
		{
			char	   *patt = TextDatumGetCString(patt_const->constvalue);

			*rest_selec = regex_selectivity(patt, strlen(patt),
											case_insensitive,
											strlen(prefix));
			pfree(patt);
		}
	}

	pfree(prefix);

	if (exact)
		return Pattern_Prefix_Exact;	/* pattern specifies exact match */
	else
		return Pattern_Prefix_Partial;
}
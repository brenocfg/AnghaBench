#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wchar_t ;
typedef  TYPE_2__* pg_locale_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ UChar ;
struct TYPE_7__ {int /*<<< orphan*/  lt; } ;
struct TYPE_8__ {scalar_t__ provider; TYPE_1__ info; } ;
typedef  scalar_t__ Oid ;

/* Variables and functions */
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_INDETERMINATE_COLLATION ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int INT_MAX ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 char* asc_initcap (char const*,size_t) ; 
 int /*<<< orphan*/  char2wchar (scalar_t__*,size_t,char const*,size_t,TYPE_2__*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  icu_convert_case (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu_from_uchar (char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icu_to_uchar (scalar_t__**,char const*,size_t) ; 
 int isalnum (unsigned char) ; 
 int isalnum_l (unsigned char,int /*<<< orphan*/ ) ; 
 int iswalnum (scalar_t__) ; 
 int iswalnum_l (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lc_ctype_is_c (scalar_t__) ; 
 char* palloc (size_t) ; 
 int /*<<< orphan*/  pfree (scalar_t__*) ; 
 size_t pg_database_encoding_max_length () ; 
 TYPE_2__* pg_newlocale_from_collation (scalar_t__) ; 
 char pg_tolower (unsigned char) ; 
 char pg_toupper (unsigned char) ; 
 char* pnstrdup (char const*,size_t) ; 
 char tolower_l (unsigned char,int /*<<< orphan*/ ) ; 
 char toupper_l (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ towlower (scalar_t__) ; 
 scalar_t__ towlower_l (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ towupper (scalar_t__) ; 
 scalar_t__ towupper_l (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_strToTitle_default_BI ; 
 int /*<<< orphan*/  wchar2char (char*,scalar_t__*,size_t,TYPE_2__*) ; 

char *
str_initcap(const char *buff, size_t nbytes, Oid collid)
{
	char	   *result;
	int			wasalnum = false;

	if (!buff)
		return NULL;

	/* C/POSIX collations use this path regardless of database encoding */
	if (lc_ctype_is_c(collid))
	{
		result = asc_initcap(buff, nbytes);
	}
	else
	{
		pg_locale_t mylocale = 0;

		if (collid != DEFAULT_COLLATION_OID)
		{
			if (!OidIsValid(collid))
			{
				/*
				 * This typically means that the parser could not resolve a
				 * conflict of implicit collations, so report it that way.
				 */
				ereport(ERROR,
						(errcode(ERRCODE_INDETERMINATE_COLLATION),
						 errmsg("could not determine which collation to use for %s function",
								"initcap()"),
						 errhint("Use the COLLATE clause to set the collation explicitly.")));
			}
			mylocale = pg_newlocale_from_collation(collid);
		}

#ifdef USE_ICU
		if (mylocale && mylocale->provider == COLLPROVIDER_ICU)
		{
			int32_t		len_uchar,
						len_conv;
			UChar	   *buff_uchar;
			UChar	   *buff_conv;

			len_uchar = icu_to_uchar(&buff_uchar, buff, nbytes);
			len_conv = icu_convert_case(u_strToTitle_default_BI, mylocale,
										&buff_conv, buff_uchar, len_uchar);
			icu_from_uchar(&result, buff_conv, len_conv);
			pfree(buff_uchar);
			pfree(buff_conv);
		}
		else
#endif
		{
			if (pg_database_encoding_max_length() > 1)
			{
				wchar_t    *workspace;
				size_t		curr_char;
				size_t		result_size;

				/* Overflow paranoia */
				if ((nbytes + 1) > (INT_MAX / sizeof(wchar_t)))
					ereport(ERROR,
							(errcode(ERRCODE_OUT_OF_MEMORY),
							 errmsg("out of memory")));

				/* Output workspace cannot have more codes than input bytes */
				workspace = (wchar_t *) palloc((nbytes + 1) * sizeof(wchar_t));

				char2wchar(workspace, nbytes + 1, buff, nbytes, mylocale);

				for (curr_char = 0; workspace[curr_char] != 0; curr_char++)
				{
#ifdef HAVE_LOCALE_T
					if (mylocale)
					{
						if (wasalnum)
							workspace[curr_char] = towlower_l(workspace[curr_char], mylocale->info.lt);
						else
							workspace[curr_char] = towupper_l(workspace[curr_char], mylocale->info.lt);
						wasalnum = iswalnum_l(workspace[curr_char], mylocale->info.lt);
					}
					else
#endif
					{
						if (wasalnum)
							workspace[curr_char] = towlower(workspace[curr_char]);
						else
							workspace[curr_char] = towupper(workspace[curr_char]);
						wasalnum = iswalnum(workspace[curr_char]);
					}
				}

				/*
				 * Make result large enough; case change might change number
				 * of bytes
				 */
				result_size = curr_char * pg_database_encoding_max_length() + 1;
				result = palloc(result_size);

				wchar2char(result, workspace, result_size, mylocale);
				pfree(workspace);
			}
			else
			{
				char	   *p;

				result = pnstrdup(buff, nbytes);

				/*
				 * Note: we assume that toupper_l()/tolower_l() will not be so
				 * broken as to need guard tests.  When using the default
				 * collation, we apply the traditional Postgres behavior that
				 * forces ASCII-style treatment of I/i, but in non-default
				 * collations you get exactly what the collation says.
				 */
				for (p = result; *p; p++)
				{
#ifdef HAVE_LOCALE_T
					if (mylocale)
					{
						if (wasalnum)
							*p = tolower_l((unsigned char) *p, mylocale->info.lt);
						else
							*p = toupper_l((unsigned char) *p, mylocale->info.lt);
						wasalnum = isalnum_l((unsigned char) *p, mylocale->info.lt);
					}
					else
#endif
					{
						if (wasalnum)
							*p = pg_tolower((unsigned char) *p);
						else
							*p = pg_toupper((unsigned char) *p);
						wasalnum = isalnum((unsigned char) *p);
					}
				}
			}
		}
	}

	return result;
}
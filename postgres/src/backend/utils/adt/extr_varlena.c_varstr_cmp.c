#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* pg_locale_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  UErrorCode ;
typedef  char UChar ;
struct TYPE_5__ {int /*<<< orphan*/  ucol; } ;
struct TYPE_6__ {int /*<<< orphan*/  lt; TYPE_1__ icu; } ;
struct TYPE_7__ {scalar_t__ provider; scalar_t__ deterministic; TYPE_2__ info; } ;
typedef  scalar_t__ Oid ;
typedef  scalar_t__* LPWSTR ;

/* Variables and functions */
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ COLLPROVIDER_LIBC ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int Min (int,int) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,scalar_t__*,int) ; 
 scalar_t__ PG_UTF8 ; 
 int TEXTBUFLEN ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  check_collation_set (scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  icu_to_uchar (char**,char const*,int) ; 
 scalar_t__ lc_collate_is_c (scalar_t__) ; 
 int memcmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 TYPE_3__* pg_newlocale_from_collation (scalar_t__) ; 
 int strcmp (char*,char*) ; 
 int strcoll (char*,char*) ; 
 int strcoll_l (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u_errorName (int /*<<< orphan*/ ) ; 
 int ucol_strcoll (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ucol_strcollUTF8 (int /*<<< orphan*/ ,char const*,int,char const*,int,int /*<<< orphan*/ *) ; 
 int wcscoll (scalar_t__*,scalar_t__*) ; 
 int wcscoll_l (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 

int
varstr_cmp(const char *arg1, int len1, const char *arg2, int len2, Oid collid)
{
	int			result;

	check_collation_set(collid);

	/*
	 * Unfortunately, there is no strncoll(), so in the non-C locale case we
	 * have to do some memory copying.  This turns out to be significantly
	 * slower, so we optimize the case where LC_COLLATE is C.  We also try to
	 * optimize relatively-short strings by avoiding palloc/pfree overhead.
	 */
	if (lc_collate_is_c(collid))
	{
		result = memcmp(arg1, arg2, Min(len1, len2));
		if ((result == 0) && (len1 != len2))
			result = (len1 < len2) ? -1 : 1;
	}
	else
	{
		char		a1buf[TEXTBUFLEN];
		char		a2buf[TEXTBUFLEN];
		char	   *a1p,
				   *a2p;
		pg_locale_t mylocale = 0;

		if (collid != DEFAULT_COLLATION_OID)
			mylocale = pg_newlocale_from_collation(collid);

		/*
		 * memcmp() can't tell us which of two unequal strings sorts first,
		 * but it's a cheap way to tell if they're equal.  Testing shows that
		 * memcmp() followed by strcoll() is only trivially slower than
		 * strcoll() by itself, so we don't lose much if this doesn't work out
		 * very often, and if it does - for example, because there are many
		 * equal strings in the input - then we win big by avoiding expensive
		 * collation-aware comparisons.
		 */
		if (len1 == len2 && memcmp(arg1, arg2, len1) == 0)
			return 0;

#ifdef WIN32
		/* Win32 does not have UTF-8, so we need to map to UTF-16 */
		if (GetDatabaseEncoding() == PG_UTF8
			&& (!mylocale || mylocale->provider == COLLPROVIDER_LIBC))
		{
			int			a1len;
			int			a2len;
			int			r;

			if (len1 >= TEXTBUFLEN / 2)
			{
				a1len = len1 * 2 + 2;
				a1p = palloc(a1len);
			}
			else
			{
				a1len = TEXTBUFLEN;
				a1p = a1buf;
			}
			if (len2 >= TEXTBUFLEN / 2)
			{
				a2len = len2 * 2 + 2;
				a2p = palloc(a2len);
			}
			else
			{
				a2len = TEXTBUFLEN;
				a2p = a2buf;
			}

			/* stupid Microsloth API does not work for zero-length input */
			if (len1 == 0)
				r = 0;
			else
			{
				r = MultiByteToWideChar(CP_UTF8, 0, arg1, len1,
										(LPWSTR) a1p, a1len / 2);
				if (!r)
					ereport(ERROR,
							(errmsg("could not convert string to UTF-16: error code %lu",
									GetLastError())));
			}
			((LPWSTR) a1p)[r] = 0;

			if (len2 == 0)
				r = 0;
			else
			{
				r = MultiByteToWideChar(CP_UTF8, 0, arg2, len2,
										(LPWSTR) a2p, a2len / 2);
				if (!r)
					ereport(ERROR,
							(errmsg("could not convert string to UTF-16: error code %lu",
									GetLastError())));
			}
			((LPWSTR) a2p)[r] = 0;

			errno = 0;
#ifdef HAVE_LOCALE_T
			if (mylocale)
				result = wcscoll_l((LPWSTR) a1p, (LPWSTR) a2p, mylocale->info.lt);
			else
#endif
				result = wcscoll((LPWSTR) a1p, (LPWSTR) a2p);
			if (result == 2147483647)	/* _NLSCMPERROR; missing from mingw
										 * headers */
				ereport(ERROR,
						(errmsg("could not compare Unicode strings: %m")));

			/* Break tie if necessary. */
			if (result == 0 &&
				(!mylocale || mylocale->deterministic))
			{
				result = memcmp(arg1, arg2, Min(len1, len2));
				if ((result == 0) && (len1 != len2))
					result = (len1 < len2) ? -1 : 1;
			}

			if (a1p != a1buf)
				pfree(a1p);
			if (a2p != a2buf)
				pfree(a2p);

			return result;
		}
#endif							/* WIN32 */

		if (len1 >= TEXTBUFLEN)
			a1p = (char *) palloc(len1 + 1);
		else
			a1p = a1buf;
		if (len2 >= TEXTBUFLEN)
			a2p = (char *) palloc(len2 + 1);
		else
			a2p = a2buf;

		memcpy(a1p, arg1, len1);
		a1p[len1] = '\0';
		memcpy(a2p, arg2, len2);
		a2p[len2] = '\0';

		if (mylocale)
		{
			if (mylocale->provider == COLLPROVIDER_ICU)
			{
#ifdef USE_ICU
#ifdef HAVE_UCOL_STRCOLLUTF8
				if (GetDatabaseEncoding() == PG_UTF8)
				{
					UErrorCode	status;

					status = U_ZERO_ERROR;
					result = ucol_strcollUTF8(mylocale->info.icu.ucol,
											  arg1, len1,
											  arg2, len2,
											  &status);
					if (U_FAILURE(status))
						ereport(ERROR,
								(errmsg("collation failed: %s", u_errorName(status))));
				}
				else
#endif
				{
					int32_t		ulen1,
								ulen2;
					UChar	   *uchar1,
							   *uchar2;

					ulen1 = icu_to_uchar(&uchar1, arg1, len1);
					ulen2 = icu_to_uchar(&uchar2, arg2, len2);

					result = ucol_strcoll(mylocale->info.icu.ucol,
										  uchar1, ulen1,
										  uchar2, ulen2);

					pfree(uchar1);
					pfree(uchar2);
				}
#else							/* not USE_ICU */
				/* shouldn't happen */
				elog(ERROR, "unsupported collprovider: %c", mylocale->provider);
#endif							/* not USE_ICU */
			}
			else
			{
#ifdef HAVE_LOCALE_T
				result = strcoll_l(a1p, a2p, mylocale->info.lt);
#else
				/* shouldn't happen */
				elog(ERROR, "unsupported collprovider: %c", mylocale->provider);
#endif
			}
		}
		else
			result = strcoll(a1p, a2p);

		/* Break tie if necessary. */
		if (result == 0 &&
			(!mylocale || mylocale->deterministic))
			result = strcmp(a1p, a2p);

		if (a1p != a1buf)
			pfree(a1p);
		if (a2p != a2buf)
			pfree(a2p);
	}

	return result;
}
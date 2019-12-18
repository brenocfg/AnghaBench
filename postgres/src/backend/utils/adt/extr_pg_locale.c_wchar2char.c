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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  TYPE_2__* pg_locale_t ;
typedef  int /*<<< orphan*/  locale_t ;
struct TYPE_4__ {int /*<<< orphan*/  lt; } ;
struct TYPE_5__ {scalar_t__ provider; TYPE_1__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COLLPROVIDER_LIBC ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ PG_UTF8 ; 
 size_t WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uselocale (int /*<<< orphan*/ ) ; 
 size_t wcstombs (char*,int /*<<< orphan*/  const*,size_t) ; 
 size_t wcstombs_l (char*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ ) ; 

size_t
wchar2char(char *to, const wchar_t *from, size_t tolen, pg_locale_t locale)
{
	size_t		result;

	Assert(!locale || locale->provider == COLLPROVIDER_LIBC);

	if (tolen == 0)
		return 0;

#ifdef WIN32

	/*
	 * On Windows, the "Unicode" locales assume UTF16 not UTF8 encoding, and
	 * for some reason mbstowcs and wcstombs won't do this for us, so we use
	 * MultiByteToWideChar().
	 */
	if (GetDatabaseEncoding() == PG_UTF8)
	{
		result = WideCharToMultiByte(CP_UTF8, 0, from, -1, to, tolen,
									 NULL, NULL);
		/* A zero return is failure */
		if (result <= 0)
			result = -1;
		else
		{
			Assert(result <= tolen);
			/* Microsoft counts the zero terminator in the result */
			result--;
		}
	}
	else
#endif							/* WIN32 */
	if (locale == (pg_locale_t) 0)
	{
		/* Use wcstombs directly for the default locale */
		result = wcstombs(to, from, tolen);
	}
	else
	{
#ifdef HAVE_LOCALE_T
#ifdef HAVE_WCSTOMBS_L
		/* Use wcstombs_l for nondefault locales */
		result = wcstombs_l(to, from, tolen, locale->info.lt);
#else							/* !HAVE_WCSTOMBS_L */
		/* We have to temporarily set the locale as current ... ugh */
		locale_t	save_locale = uselocale(locale->info.lt);

		result = wcstombs(to, from, tolen);

		uselocale(save_locale);
#endif							/* HAVE_WCSTOMBS_L */
#else							/* !HAVE_LOCALE_T */
		/* Can't have locale != 0 without HAVE_LOCALE_T */
		elog(ERROR, "wcstombs_l is not available");
		result = 0;				/* keep compiler quiet */
#endif							/* HAVE_LOCALE_T */
	}

	return result;
}
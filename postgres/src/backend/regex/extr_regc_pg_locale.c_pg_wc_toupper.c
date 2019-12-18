#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  scalar_t__ pg_wchar ;
struct TYPE_3__ {int /*<<< orphan*/  lt; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
#define  PG_REGEX_LOCALE_1BYTE 133 
#define  PG_REGEX_LOCALE_1BYTE_L 132 
#define  PG_REGEX_LOCALE_C 131 
#define  PG_REGEX_LOCALE_ICU 130 
#define  PG_REGEX_LOCALE_WIDE 129 
#define  PG_REGEX_LOCALE_WIDE_L 128 
 int /*<<< orphan*/  UCHAR_MAX ; 
 scalar_t__ pg_ascii_toupper (unsigned char) ; 
 TYPE_2__* pg_regex_locale ; 
 int pg_regex_strategy ; 
 scalar_t__ toupper (unsigned char) ; 
 scalar_t__ toupper_l (unsigned char,int /*<<< orphan*/ ) ; 
 scalar_t__ towupper (int /*<<< orphan*/ ) ; 
 scalar_t__ towupper_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ u_toupper (scalar_t__) ; 

__attribute__((used)) static pg_wchar
pg_wc_toupper(pg_wchar c)
{
	switch (pg_regex_strategy)
	{
		case PG_REGEX_LOCALE_C:
			if (c <= (pg_wchar) 127)
				return pg_ascii_toupper((unsigned char) c);
			return c;
		case PG_REGEX_LOCALE_WIDE:
			/* force C behavior for ASCII characters, per comments above */
			if (c <= (pg_wchar) 127)
				return pg_ascii_toupper((unsigned char) c);
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return towupper((wint_t) c);
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE:
			/* force C behavior for ASCII characters, per comments above */
			if (c <= (pg_wchar) 127)
				return pg_ascii_toupper((unsigned char) c);
			if (c <= (pg_wchar) UCHAR_MAX)
				return toupper((unsigned char) c);
			return c;
		case PG_REGEX_LOCALE_WIDE_L:
#ifdef HAVE_LOCALE_T
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return towupper_l((wint_t) c, pg_regex_locale->info.lt);
#endif
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE_L:
#ifdef HAVE_LOCALE_T
			if (c <= (pg_wchar) UCHAR_MAX)
				return toupper_l((unsigned char) c, pg_regex_locale->info.lt);
#endif
			return c;
		case PG_REGEX_LOCALE_ICU:
#ifdef USE_ICU
			return u_toupper(c);
#endif
			break;
	}
	return 0;					/* can't get here, but keep compiler quiet */
}
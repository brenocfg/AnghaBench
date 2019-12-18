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
typedef  size_t pg_wchar ;
struct TYPE_3__ {int /*<<< orphan*/  lt; } ;
struct TYPE_4__ {TYPE_1__ info; } ;

/* Variables and functions */
 int PG_ISGRAPH ; 
#define  PG_REGEX_LOCALE_1BYTE 133 
#define  PG_REGEX_LOCALE_1BYTE_L 132 
#define  PG_REGEX_LOCALE_C 131 
#define  PG_REGEX_LOCALE_ICU 130 
#define  PG_REGEX_LOCALE_WIDE 129 
#define  PG_REGEX_LOCALE_WIDE_L 128 
 int /*<<< orphan*/  UCHAR_MAX ; 
 int /*<<< orphan*/  isgraph (unsigned char) ; 
 int /*<<< orphan*/  isgraph_l (unsigned char,int /*<<< orphan*/ ) ; 
 int iswgraph (int /*<<< orphan*/ ) ; 
 int iswgraph_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pg_char_properties ; 
 TYPE_2__* pg_regex_locale ; 
 int pg_regex_strategy ; 
 int u_isgraph (size_t) ; 

__attribute__((used)) static int
pg_wc_isgraph(pg_wchar c)
{
	switch (pg_regex_strategy)
	{
		case PG_REGEX_LOCALE_C:
			return (c <= (pg_wchar) 127 &&
					(pg_char_properties[c] & PG_ISGRAPH));
		case PG_REGEX_LOCALE_WIDE:
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return iswgraph((wint_t) c);
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE:
			return (c <= (pg_wchar) UCHAR_MAX &&
					isgraph((unsigned char) c));
		case PG_REGEX_LOCALE_WIDE_L:
#ifdef HAVE_LOCALE_T
			if (sizeof(wchar_t) >= 4 || c <= (pg_wchar) 0xFFFF)
				return iswgraph_l((wint_t) c, pg_regex_locale->info.lt);
#endif
			/* FALL THRU */
		case PG_REGEX_LOCALE_1BYTE_L:
#ifdef HAVE_LOCALE_T
			return (c <= (pg_wchar) UCHAR_MAX &&
					isgraph_l((unsigned char) c, pg_regex_locale->info.lt));
#endif
			break;
		case PG_REGEX_LOCALE_ICU:
#ifdef USE_ICU
			return u_isgraph(c);
#endif
			break;
	}
	return 0;					/* can't get here, but keep compiler quiet */
}
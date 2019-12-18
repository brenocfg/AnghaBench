#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  pg_locale_t ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  TOUCHAR (char const*) ; 
 int WC_BUF_LEN ; 
 int /*<<< orphan*/  char2wchar (scalar_t__*,int,char const*,int,int /*<<< orphan*/ ) ; 
 int isprint (int /*<<< orphan*/ ) ; 
 int iswprint (int /*<<< orphan*/ ) ; 
 scalar_t__ lc_ctype_is_c (int /*<<< orphan*/ ) ; 
 int pg_mblen (char const*) ; 

int
t_isprint(const char *ptr)
{
	int			clen = pg_mblen(ptr);
	wchar_t		character[WC_BUF_LEN];
	Oid			collation = DEFAULT_COLLATION_OID;	/* TODO */
	pg_locale_t mylocale = 0;	/* TODO */

	if (clen == 1 || lc_ctype_is_c(collation))
		return isprint(TOUCHAR(ptr));

	char2wchar(character, WC_BUF_LEN, ptr, clen, mylocale);

	return iswprint((wint_t) character[0]);
}
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
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERRCODE_CHARACTER_NOT_IN_REPERTOIRE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  TOUCHAR (char const*) ; 
 int char2wchar (scalar_t__*,int,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  lc_ctype_is_c (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (scalar_t__*) ; 
 int pg_database_encoding_max_length () ; 
 char* pstrdup (char*) ; 
 int /*<<< orphan*/  tolower (int /*<<< orphan*/ ) ; 
 scalar_t__ towlower (int /*<<< orphan*/ ) ; 
 int wchar2char (char*,scalar_t__*,int,int /*<<< orphan*/ ) ; 

char *
lowerstr_with_len(const char *str, int len)
{
	char	   *out;
	Oid			collation = DEFAULT_COLLATION_OID;	/* TODO */
	pg_locale_t mylocale = 0;	/* TODO */

	if (len == 0)
		return pstrdup("");

	/*
	 * Use wide char code only when max encoding length > 1 and ctype != C.
	 * Some operating systems fail with multi-byte encodings and a C locale.
	 * Also, for a C locale there is no need to process as multibyte. From
	 * backend/utils/adt/oracle_compat.c Teodor
	 */
	if (pg_database_encoding_max_length() > 1 && !lc_ctype_is_c(collation))
	{
		wchar_t    *wstr,
				   *wptr;
		int			wlen;

		/*
		 * alloc number of wchar_t for worst case, len contains number of
		 * bytes >= number of characters and alloc 1 wchar_t for 0, because
		 * wchar2char wants zero-terminated string
		 */
		wptr = wstr = (wchar_t *) palloc(sizeof(wchar_t) * (len + 1));

		wlen = char2wchar(wstr, len + 1, str, len, mylocale);
		Assert(wlen <= len);

		while (*wptr)
		{
			*wptr = towlower((wint_t) *wptr);
			wptr++;
		}

		/*
		 * Alloc result string for worst case + '\0'
		 */
		len = pg_database_encoding_max_length() * wlen + 1;
		out = (char *) palloc(len);

		wlen = wchar2char(out, wstr, len, mylocale);

		pfree(wstr);

		if (wlen < 0)
			ereport(ERROR,
					(errcode(ERRCODE_CHARACTER_NOT_IN_REPERTOIRE),
					 errmsg("conversion from wchar_t to server encoding failed: %m")));
		Assert(wlen < len);
	}
	else
	{
		const char *ptr = str;
		char	   *outptr;

		outptr = out = (char *) palloc(sizeof(char) * (len + 1));
		while ((ptr - str) < len && *ptr)
		{
			*outptr++ = tolower(TOUCHAR(ptr));
			ptr++;
		}
		*outptr = '\0';
	}

	return out;
}
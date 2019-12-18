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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  pg_wchar ;
typedef  int /*<<< orphan*/  errMsg ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_REGULAR_EXPRESSION ; 
 int /*<<< orphan*/  ERROR ; 
 int REG_OKAY ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int pg_mb2wchar_with_len (char*,int /*<<< orphan*/ *,int) ; 
 int pg_regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_regerror (int,int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void
RE_compile(regex_t *regex, text *text_re, int cflags, Oid collation)
{
	int			text_re_len = VARSIZE_ANY_EXHDR(text_re);
	char	   *text_re_val = VARDATA_ANY(text_re);
	pg_wchar   *pattern;
	int			pattern_len;
	int			regcomp_result;
	char		errMsg[100];

	/* Convert pattern string to wide characters */
	pattern = (pg_wchar *) palloc((text_re_len + 1) * sizeof(pg_wchar));
	pattern_len = pg_mb2wchar_with_len(text_re_val,
									   pattern,
									   text_re_len);

	/* Compile regex */
	regcomp_result = pg_regcomp(regex,
								pattern,
								pattern_len,
								cflags,
								collation);

	pfree(pattern);

	if (regcomp_result != REG_OKAY)
	{
		/* re didn't compile (no need for pg_regfree, if so) */
		pg_regerror(regcomp_result, regex, errMsg, sizeof(errMsg));
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_REGULAR_EXPRESSION),
				 errmsg("invalid regular expression: %s", errMsg)));
	}
}
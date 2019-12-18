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

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int PG_SQL_ASCII ; 
 int PG_UTF8 ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pg_encoding_to_char (int) ; 
 int pg_get_encoding_from_locale (char const*,int) ; 
 scalar_t__ superuser () ; 

void
check_encoding_locale_matches(int encoding, const char *collate, const char *ctype)
{
	int			ctype_encoding = pg_get_encoding_from_locale(ctype, true);
	int			collate_encoding = pg_get_encoding_from_locale(collate, true);

	if (!(ctype_encoding == encoding ||
		  ctype_encoding == PG_SQL_ASCII ||
		  ctype_encoding == -1 ||
#ifdef WIN32
		  encoding == PG_UTF8 ||
#endif
		  (encoding == PG_SQL_ASCII && superuser())))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("encoding \"%s\" does not match locale \"%s\"",
						pg_encoding_to_char(encoding),
						ctype),
				 errdetail("The chosen LC_CTYPE setting requires encoding \"%s\".",
						   pg_encoding_to_char(ctype_encoding))));

	if (!(collate_encoding == encoding ||
		  collate_encoding == PG_SQL_ASCII ||
		  collate_encoding == -1 ||
#ifdef WIN32
		  encoding == PG_UTF8 ||
#endif
		  (encoding == PG_SQL_ASCII && superuser())))
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
				 errmsg("encoding \"%s\" does not match locale \"%s\"",
						pg_encoding_to_char(encoding),
						collate),
				 errdetail("The chosen LC_COLLATE setting requires encoding \"%s\".",
						   pg_encoding_to_char(collate_encoding))));
}
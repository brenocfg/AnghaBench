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
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ PG_ENCODING_BE_LAST ; 
 int /*<<< orphan*/  StaticAssertStmt (int,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lengthof (char**) ; 
 char** pg_enc2icu_tbl ; 
 int /*<<< orphan*/  pg_encoding_to_char (int) ; 

const char *
get_encoding_name_for_icu(int encoding)
{
	const char *icu_encoding_name;

	StaticAssertStmt(lengthof(pg_enc2icu_tbl) == PG_ENCODING_BE_LAST + 1,
					 "pg_enc2icu_tbl incomplete");

	icu_encoding_name = pg_enc2icu_tbl[encoding];

	if (!icu_encoding_name)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("encoding \"%s\" not supported by ICU",
						pg_encoding_to_char(encoding))));

	return icu_encoding_name;
}
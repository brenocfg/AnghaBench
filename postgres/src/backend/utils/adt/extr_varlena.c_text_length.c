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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_RETURN_INT32 (scalar_t__) ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int pg_database_encoding_max_length () ; 
 scalar_t__ pg_mbstrlen_with_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ toast_raw_datum_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
text_length(Datum str)
{
	/* fastpath when max encoding length is one */
	if (pg_database_encoding_max_length() == 1)
		PG_RETURN_INT32(toast_raw_datum_size(str) - VARHDRSZ);
	else
	{
		text	   *t = DatumGetTextPP(str);

		PG_RETURN_INT32(pg_mbstrlen_with_len(VARDATA_ANY(t),
											 VARSIZE_ANY_EXHDR(t)));
	}
}
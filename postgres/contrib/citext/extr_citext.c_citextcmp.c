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
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* str_tolower (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  varstr_cmp (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
citextcmp(text *left, text *right, Oid collid)
{
	char	   *lcstr,
			   *rcstr;
	int32		result;

	/*
	 * We must do our str_tolower calls with DEFAULT_COLLATION_OID, not the
	 * input collation as you might expect.  This is so that the behavior of
	 * citext's equality and hashing functions is not collation-dependent.  We
	 * should change this once the core infrastructure is able to cope with
	 * collation-dependent equality and hashing functions.
	 */

	lcstr = str_tolower(VARDATA_ANY(left), VARSIZE_ANY_EXHDR(left), DEFAULT_COLLATION_OID);
	rcstr = str_tolower(VARDATA_ANY(right), VARSIZE_ANY_EXHDR(right), DEFAULT_COLLATION_OID);

	result = varstr_cmp(lcstr, strlen(lcstr),
						rcstr, strlen(rcstr),
						collid);

	pfree(lcstr);
	pfree(rcstr);

	return result;
}
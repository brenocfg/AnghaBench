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
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  STRLEN ;

/* Variables and functions */
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ PG_SQL_ASCII ; 
 scalar_t__ SVt_PVFM ; 
 scalar_t__ SVt_PVLV ; 
 char* SvPV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* SvPVutf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SvREADONLY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvREFCNT_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SvREFCNT_inc_simple_void (int /*<<< orphan*/ *) ; 
 scalar_t__ SvTYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 scalar_t__ isGV_with_GP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSVsv (int /*<<< orphan*/ *) ; 
 char* utf_u2e (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline char *
sv2cstr(SV *sv)
{
	dTHX;
	char	   *val,
			   *res;
	STRLEN		len;

	/*
	 * get a utf8 encoded char * out of perl. *note* it may not be valid utf8!
	 */

	/*
	 * SvPVutf8() croaks nastily on certain things, like typeglobs and
	 * readonly objects such as $^V. That's a perl bug - it's not supposed to
	 * happen. To avoid crashing the backend, we make a copy of the sv before
	 * passing it to SvPVutf8(). The copy is garbage collected when we're done
	 * with it.
	 */
	if (SvREADONLY(sv) ||
		isGV_with_GP(sv) ||
		(SvTYPE(sv) > SVt_PVLV && SvTYPE(sv) != SVt_PVFM))
		sv = newSVsv(sv);
	else
	{
		/*
		 * increase the reference count so we can just SvREFCNT_dec() it when
		 * we are done
		 */
		SvREFCNT_inc_simple_void(sv);
	}

	/*
	 * Request the string from Perl, in UTF-8 encoding; but if we're in a
	 * SQL_ASCII database, just request the byte soup without trying to make
	 * it UTF8, because that might fail.
	 */
	if (GetDatabaseEncoding() == PG_SQL_ASCII)
		val = SvPV(sv, len);
	else
		val = SvPVutf8(sv, len);

	/*
	 * Now convert to database encoding.  We use perl's length in the event we
	 * had an embedded null byte to ensure we error out properly.
	 */
	res = utf_u2e(val, len);

	/* safe now to garbage collect the new SV */
	SvREFCNT_dec(sv);

	return res;
}
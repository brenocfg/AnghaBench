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

/* Variables and functions */
 scalar_t__ GetDatabaseEncoding () ; 
 scalar_t__ PG_SQL_ASCII ; 
 int /*<<< orphan*/  SvUTF8_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ * newSVpv (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* utf_e2u (char const*) ; 

__attribute__((used)) static inline SV *
cstr2sv(const char *str)
{
	dTHX;
	SV		   *sv;
	char	   *utf8_str;

	/* no conversion when SQL_ASCII */
	if (GetDatabaseEncoding() == PG_SQL_ASCII)
		return newSVpv(str, 0);

	utf8_str = utf_e2u(str);

	sv = newSVpv(utf8_str, 0);
	SvUTF8_on(sv);
	pfree(utf8_str);

	return sv;
}
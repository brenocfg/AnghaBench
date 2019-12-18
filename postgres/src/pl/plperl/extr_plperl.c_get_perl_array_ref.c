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
typedef  int /*<<< orphan*/  HV ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SVt_PVAV ; 
 scalar_t__ SvOK (int /*<<< orphan*/ *) ; 
 scalar_t__ SvROK (int /*<<< orphan*/ *) ; 
 scalar_t__ SvRV (int /*<<< orphan*/ *) ; 
 scalar_t__ SvTYPE (scalar_t__) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ ** hv_fetch_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sv_isa (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static SV  *
get_perl_array_ref(SV *sv)
{
	dTHX;

	if (SvOK(sv) && SvROK(sv))
	{
		if (SvTYPE(SvRV(sv)) == SVt_PVAV)
			return sv;
		else if (sv_isa(sv, "PostgreSQL::InServer::ARRAY"))
		{
			HV		   *hv = (HV *) SvRV(sv);
			SV		  **sav = hv_fetch_string(hv, "array");

			if (*sav && SvOK(*sav) && SvROK(*sav) &&
				SvTYPE(SvRV(*sav)) == SVt_PVAV)
				return *sav;

			elog(ERROR, "could not get array reference from PostgreSQL::InServer::ARRAY object");
		}
	}
	return NULL;
}
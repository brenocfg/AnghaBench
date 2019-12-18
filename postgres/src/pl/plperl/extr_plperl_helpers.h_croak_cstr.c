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
 int /*<<< orphan*/  GV_ADD ; 
 int /*<<< orphan*/  SvUTF8_on (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  croak (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  croak_sv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cstr2sv (char const*) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/ * get_sv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mess (char*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  sv_2mortal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv_setsv (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* utf_e2u (char const*) ; 

__attribute__((used)) static inline void
croak_cstr(const char *str)
{
	dTHX;

#ifdef croak_sv
	/* Use sv_2mortal() to be sure the transient SV gets freed */
	croak_sv(sv_2mortal(cstr2sv(str)));
#else

	/*
	 * The older way to do this is to assign a UTF8-marked value to ERRSV and
	 * then call croak(NULL).  But if we leave it to croak() to append the
	 * error location, it does so too late (only after popping the stack) in
	 * some Perl versions.  Hence, use mess() to create an SV with the error
	 * location info already appended.
	 */
	SV		   *errsv = get_sv("@", GV_ADD);
	char	   *utf8_str = utf_e2u(str);
	SV		   *ssv;

	ssv = mess("%s", utf8_str);
	SvUTF8_on(ssv);

	pfree(utf8_str);

	sv_setsv(errsv, ssv);

	croak(NULL);
#endif							/* croak_sv */
}
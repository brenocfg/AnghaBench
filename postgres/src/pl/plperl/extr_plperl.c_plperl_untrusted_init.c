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
 int /*<<< orphan*/  ERRCODE_EXTERNAL_ROUTINE_EXCEPTION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ERRSV ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SvTRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcontext (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eval_pv (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* plperl_on_plperlu_init ; 
 int /*<<< orphan*/  strip_trailing_ws (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sv2cstr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
plperl_untrusted_init(void)
{
	dTHX;

	/*
	 * Nothing to do except execute plperl.on_plperlu_init
	 */
	if (plperl_on_plperlu_init && *plperl_on_plperlu_init)
	{
		eval_pv(plperl_on_plperlu_init, FALSE);
		if (SvTRUE(ERRSV))
			ereport(ERROR,
					(errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
					 errmsg("%s", strip_trailing_ws(sv2cstr(ERRSV))),
					 errcontext("while executing plperl.on_plperlu_init")));
	}
}
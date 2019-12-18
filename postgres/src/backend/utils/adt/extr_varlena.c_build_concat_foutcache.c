#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * fn_extra; int /*<<< orphan*/  fn_mcxt; } ;
struct TYPE_4__ {TYPE_2__* flinfo; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* FunctionCallInfo ;
typedef  int /*<<< orphan*/  FmgrInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ MemoryContextAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int PG_NARGS () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_fn_expr_argtype (TYPE_2__*,int) ; 

__attribute__((used)) static FmgrInfo *
build_concat_foutcache(FunctionCallInfo fcinfo, int argidx)
{
	FmgrInfo   *foutcache;
	int			i;

	/* We keep the info in fn_mcxt so it survives across calls */
	foutcache = (FmgrInfo *) MemoryContextAlloc(fcinfo->flinfo->fn_mcxt,
												PG_NARGS() * sizeof(FmgrInfo));

	for (i = argidx; i < PG_NARGS(); i++)
	{
		Oid			valtype;
		Oid			typOutput;
		bool		typIsVarlena;

		valtype = get_fn_expr_argtype(fcinfo->flinfo, i);
		if (!OidIsValid(valtype))
			elog(ERROR, "could not determine data type of concat() input");

		getTypeOutputInfo(valtype, &typOutput, &typIsVarlena);
		fmgr_info_cxt(typOutput, &foutcache[i], fcinfo->flinfo->fn_mcxt);
	}

	fcinfo->flinfo->fn_extra = foutcache;

	return foutcache;
}
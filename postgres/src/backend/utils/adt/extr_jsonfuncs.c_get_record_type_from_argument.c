#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ typcat; } ;
struct TYPE_7__ {int /*<<< orphan*/  flinfo; } ;
struct TYPE_6__ {TYPE_3__ c; int /*<<< orphan*/  fn_mcxt; int /*<<< orphan*/  argtype; } ;
typedef  TYPE_1__ PopulateRecordCache ;
typedef  TYPE_2__* FunctionCallInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ TYPECAT_COMPOSITE ; 
 scalar_t__ TYPECAT_COMPOSITE_DOMAIN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int /*<<< orphan*/  get_fn_expr_argtype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_column_cache (TYPE_3__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
get_record_type_from_argument(FunctionCallInfo fcinfo,
							  const char *funcname,
							  PopulateRecordCache *cache)
{
	cache->argtype = get_fn_expr_argtype(fcinfo->flinfo, 0);
	prepare_column_cache(&cache->c,
						 cache->argtype, -1,
						 cache->fn_mcxt, false);
	if (cache->c.typcat != TYPECAT_COMPOSITE &&
		cache->c.typcat != TYPECAT_COMPOSITE_DOMAIN)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
		/* translator: %s is a function name, eg json_to_record */
				 errmsg("first argument of %s must be a row type",
						funcname)));
}
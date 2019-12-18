#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct config_bool {TYPE_1__ gen; int /*<<< orphan*/  (* check_hook ) (int*,void**,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  FlushErrorState () ; 
 int /*<<< orphan*/  GUC_check_errcode_value ; 
 int /*<<< orphan*/ * GUC_check_errdetail_string ; 
 int /*<<< orphan*/ * GUC_check_errhint_string ; 
 int /*<<< orphan*/ * GUC_check_errmsg_string ; 
 int /*<<< orphan*/  ereport (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errmsg_internal (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int*,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
call_bool_check_hook(struct config_bool *conf, bool *newval, void **extra,
					 GucSource source, int elevel)
{
	/* Quick success if no hook */
	if (!conf->check_hook)
		return true;

	/* Reset variables that might be set by hook */
	GUC_check_errcode_value = ERRCODE_INVALID_PARAMETER_VALUE;
	GUC_check_errmsg_string = NULL;
	GUC_check_errdetail_string = NULL;
	GUC_check_errhint_string = NULL;

	if (!conf->check_hook(newval, extra, source))
	{
		ereport(elevel,
				(errcode(GUC_check_errcode_value),
				 GUC_check_errmsg_string ?
				 errmsg_internal("%s", GUC_check_errmsg_string) :
				 errmsg("invalid value for parameter \"%s\": %d",
						conf->gen.name, (int) *newval),
				 GUC_check_errdetail_string ?
				 errdetail_internal("%s", GUC_check_errdetail_string) : 0,
				 GUC_check_errhint_string ?
				 errhint("%s", GUC_check_errhint_string) : 0));
		/* Flush any strings created in ErrorContext */
		FlushErrorState();
		return false;
	}

	return true;
}
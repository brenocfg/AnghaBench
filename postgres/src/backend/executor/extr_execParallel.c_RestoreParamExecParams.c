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
struct TYPE_5__ {TYPE_1__* es_param_exec_vals; } ;
struct TYPE_4__ {int /*<<< orphan*/ * execPlan; int /*<<< orphan*/  isnull; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ParamExecData ;
typedef  TYPE_2__ EState ;

/* Variables and functions */
 int /*<<< orphan*/  datumRestore (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 

__attribute__((used)) static void
RestoreParamExecParams(char *start_address, EState *estate)
{
	int			nparams;
	int			i;
	int			paramid;

	memcpy(&nparams, start_address, sizeof(int));
	start_address += sizeof(int);

	for (i = 0; i < nparams; i++)
	{
		ParamExecData *prm;

		/* Read paramid */
		memcpy(&paramid, start_address, sizeof(int));
		start_address += sizeof(int);
		prm = &(estate->es_param_exec_vals[paramid]);

		/* Read datum/isnull. */
		prm->value = datumRestore(&start_address, &prm->isnull);
		prm->execPlan = NULL;
	}
}
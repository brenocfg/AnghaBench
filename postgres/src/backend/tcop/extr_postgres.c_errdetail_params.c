#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  value; int /*<<< orphan*/  ptype; scalar_t__ isnull; } ;
struct TYPE_10__ {scalar_t__ numParams; TYPE_3__* params; int /*<<< orphan*/ * paramFetch; } ;
struct TYPE_9__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__* ParamListInfo ;
typedef  TYPE_3__ ParamExternData ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsAbortedTransactionBlockState () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MessageContext ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  appendStringInfoCharMacro (TYPE_1__*,char) ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  errdetail (char*,char*) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static int
errdetail_params(ParamListInfo params)
{
	/* We mustn't call user-defined I/O functions when in an aborted xact */
	if (params && params->numParams > 0 && !IsAbortedTransactionBlockState())
	{
		StringInfoData param_str;
		MemoryContext oldcontext;

		/* This code doesn't support dynamic param lists */
		Assert(params->paramFetch == NULL);

		/* Make sure any trash is generated in MessageContext */
		oldcontext = MemoryContextSwitchTo(MessageContext);

		initStringInfo(&param_str);

		for (int paramno = 0; paramno < params->numParams; paramno++)
		{
			ParamExternData *prm = &params->params[paramno];
			Oid			typoutput;
			bool		typisvarlena;
			char	   *pstring;
			char	   *p;

			appendStringInfo(&param_str, "%s$%d = ",
							 paramno > 0 ? ", " : "",
							 paramno + 1);

			if (prm->isnull || !OidIsValid(prm->ptype))
			{
				appendStringInfoString(&param_str, "NULL");
				continue;
			}

			getTypeOutputInfo(prm->ptype, &typoutput, &typisvarlena);

			pstring = OidOutputFunctionCall(typoutput, prm->value);

			appendStringInfoCharMacro(&param_str, '\'');
			for (p = pstring; *p; p++)
			{
				if (*p == '\'') /* double single quotes */
					appendStringInfoCharMacro(&param_str, *p);
				appendStringInfoCharMacro(&param_str, *p);
			}
			appendStringInfoCharMacro(&param_str, '\'');

			pfree(pstring);
		}

		errdetail("parameters: %s", param_str.data);

		pfree(param_str.data);

		MemoryContextSwitchTo(oldcontext);
	}

	return 0;
}